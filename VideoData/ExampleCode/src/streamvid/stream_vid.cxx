/*
* (c) Copyright, Real-Time Innovations, 2021. All rights reserved.
* RTI grants Licensee a license to use, modify, compile, and create derivative
* works of the software solely for use with RTI Connext DDS. Licensee may
* redistribute copies of the software provided that all such copies are subject
* to this license. The software is provided "as is", with no warranty of any
* type, including any warranty for fitness for any purpose. RTI is under no
* obligation to maintain or support the software. RTI shall not be liable for
* any incidental or consequential damages arising out of the use or inability
* to use the software.
*/
/**
 * stream_vid: Video streaming example application.
 * This works with an external FFMPEG(for encoding) and FFPLAY(for decoding/display)
 *  connected to this application via a local UDP connection to loopback address.
 * This example works as pub/sub pair to send video/audio, encoded as MPEG-TS or 
 *  other streaming protocol over a DDS connection using any supported transport.
 *  (UDP-LAN, UDP-WAN(Connext Anywhere), etc.).
 * Best Effort QoS is used by default in preparation for internet traversal.
 **/
#include <algorithm>
#include <iostream>
#include <thread>                   // thread for UDP input from ffmpeg(blocking)
#include <mutex>                    // signalling between thread and main 
#include <condition_variable>       // signalling between thread and main
#include <signal.h>                 // ctrl-c handler
#ifdef WIN32
#include <WinSock2.h>               // Windows UDP support
#else                               // Linux UDP support
#include <arpa/inet.h>              // htons, inet_addr
#include <netinet/in.h>             // sockaddr_in
#include <sys/types.h>              // uint16_t
#include <sys/socket.h>             // socket, sendto
#include <unistd.h>                 // close
#endif
#include <rti/util/util.hpp>        // for sleep() 
#include "rti_comms.hpp"            // for Connext DDS pub/sub of bulk streaming topic
#include "murmurhash3.h"            // for hashing
#include "streamvid/app_helper.hpp" // for command line args and signals, name hashing

// This sets the UDP socket connection between FFMPEG/FFPLAY and this example
std::string hostname("127.0.0.1");
uint16_t port_base = 2277;          // Note: FFMPEG uses this port, FFPLAY is at this port + 1
sockaddr_in destination;
#ifdef WIN32
SOCKET destSocket = INVALID_SOCKET;
#else  // Linux
int sock;
#endif
// this uses a common buffer to pass data from UDP thread to DDS exporter
char* tmpBuf;
const int32_t tmpBufMax = 1048576;
uint32_t inx, outx, rollx;
uint64_t intot, outtot;
// mutex & condition variable for synchronization (thread to main)
std::condition_variable cv;
std::mutex mtx;


/** ----------------------------------------------------------------
 * vid_data_sub()
 * handler (callback) for received video samples sent by vidPub
 **/
int vid_data_sub(dds::sub::DataReader<cctypes::ccBulk> reader)
{
    // Take all samples
    int count = 0;
    dds::sub::LoanedSamples<cctypes::ccBulk> samples = reader.take();
    for (const auto& sample : samples) {
        if (sample.info().valid()) {
            // write the data to external FFMPEG via UDP socket, in 188-byte(max) chunks
            int32_t dataSize = (int32_t)sample.data().data().size();
            uint32_t chunk = 0;
            for (size_t i = 0; i < dataSize;) {
                if ((dataSize - i) > 188) { chunk = 188; }
                else { chunk = (uint32_t)(dataSize - i); }
#ifdef WIN32
                i += sendto(destSocket, reinterpret_cast<const char*>(sample.data().data().data() + i),
                    chunk, 0, (sockaddr*)&destination, sizeof(destination));
#else
                i += ::sendto(sock, sample.data().data().data() + i, chunk, 0,
                    reinterpret_cast<sockaddr*>(&destination), sizeof(destination));
#endif
            }
            count++;
        }
        else {
            std::cout << "Instance state changed to "
                << sample.info().state().instance_state() << std::endl;
        }
    }
    return count;
}


/** ----------------------------------------------------------------
 * udp_input_thread()
 * This is a separate thread for receiving UDP input from FFMPEG
 **/
void udp_input_thread(void)
{
#ifdef WIN32
    WSADATA wsaData;
    int res = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (res != NO_ERROR) {
        printf("WSAStartup failed with error %d\n", res);
        return;
    }

    destSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (destSocket == INVALID_SOCKET) {
        printf("socket failed with error %d\n", WSAGetLastError());
        return;
    }

    // Bind the socket to the specified address and port.
    destination.sin_family = AF_INET;
    destination.sin_port = htons(port_base);
    destination.sin_addr.s_addr = inet_addr(hostname.c_str());

    if (bind(destSocket, (SOCKADDR*)&destination, sizeof(destination))) {
        printf("bind failed with error %d\n", WSAGetLastError());
        return;
    }
    int destAddrSize = sizeof(destination);
#else   // Linux
    sock = ::socket(AF_INET, SOCK_DGRAM, 0);
    destination.sin_family = AF_INET;
    destination.sin_port = htons(port_base);
    destination.sin_addr.s_addr = inet_addr(hostname.c_str());

    //checks connection
    if (bind(sock, (struct sockaddr*)&destination, sizeof(destination)) < 0) {
        std::cout << "UDP Connection error" << std::endl;
    }
#endif
    int udp_bytes_rcvd = 0;

    while (false == application::shutdown_requested)
    {
        // this call blocks until data is received
#ifdef WIN32
        udp_bytes_rcvd = recvfrom(destSocket, &tmpBuf[inx], 1504,
            0, (SOCKADDR*)&destination, &destAddrSize);
        if (udp_bytes_rcvd == SOCKET_ERROR) {
            printf("recvfrom failed with error %d\n", WSAGetLastError());
        }
#else   // Linux
        int udp_bytes_rcvd = recv(sock, &tmpBuf[inx], 2048, 0);
        if (udp_bytes_rcvd < 0) {
            std::cout << "recv failed" << std::endl;
        }
#endif
        intot += udp_bytes_rcvd;
        inx += udp_bytes_rcvd;
        if (inx > rollx) rollx = inx;

        /* wrap the buffer if either: very close to end, 
           or if near the end and a chunk of data < 1472 bytes
           was just received, as these tend to help align the send buffer
           with the MPEG-TS packets (which are 188 bytes in length)
        */
        if (((inx > ((7 * tmpBufMax) / 8)) && (udp_bytes_rcvd < 1472))
            || ((inx + 1472) >= tmpBufMax))
        {
            rollx = inx;
            inx = 0;
        }

        // notify pub loop: there is data to send
        std::lock_guard<std::mutex> lk(mtx);
        cv.notify_one();
    }
    return;
}

/** ----------------------------------------------------------------
 * participant_main()
 **/
void participant_main(application::ApplicationArguments args)
{
    // setup ----------------------------------------------------
    // convert names to ID strings (used as DDS topic name)
    std::string myId, fromId;
    application::contact_name_to_id(args.this_station_name, myId);
    application::contact_name_to_id(args.from_station_name, fromId);

    if (args.is_vid_pub) {
        fprintf(stderr, "This Station: %s publishing on topic: '%s'\n", args.this_station_name.c_str(), myId.c_str());
    }
    else {
        fprintf(stderr, "This Station: %s subscribing to topic: '%s'\n", args.this_station_name.c_str(), fromId.c_str());
    }

    // set the default QoS from the args (a, b or c)
    dds::core::QosProvider::Default()->default_profile(std::string("UserQosProfilesLibrary::profile_" + args.qos_profile));

    // Create a DomainParticipant with default Qos
    dds::domain::DomainParticipant participant(args.domain_id);

    // Instantiate a class wrapper for the Connext pub or sub, BestEffort QoS
    uint32_t cnxDir = 0;
    std::string topicId;
    if (args.is_vid_pub) {
        cnxDir = CTRL_PUB_BE;
        topicId = "v" + myId;
    }
    else {
        cnxDir = CTRL_SUB_BE;
        topicId = "v" + fromId;
    }
    dds::core::cond::WaitSet waitset;
    rtiComms cnxStream(topicId, cnxDir, participant, &waitset, &vid_data_sub);


    // publisher ---------------------------------------------------
    if (args.is_vid_pub) {
        cnxStream.pub_sample_data_size_set(args.data_sample_size);
        if ((tmpBuf = (char*)calloc(tmpBufMax, sizeof(char))) == NULL) {
            fprintf(stderr, "Memory Allocation error at %s:%d\n", __FILE__, __LINE__);
            exit(-1);
        }

        inx = outx = 0;
        rollx = tmpBufMax;
        intot = outtot = 0;

        // launch thread for udp input from FFMPEG
        std::thread thrudp(udp_input_thread);
        thrudp.detach();

        // publish loop
        while (false == application::shutdown_requested) {
            // Wait (block) until there's data to send (from UDP input thread)
            // or if >1 second without data (unblock for ctrl-c exit)
            std::unique_lock<std::mutex> lk(mtx);
            cv.wait_for(lk, std::chrono::seconds(1));

            //  publish all available data as DDS samples
            while ((intot - outtot) > args.data_sample_size)
            {
                if ((outx + (int)args.data_sample_size) <= rollx)
                {
                    memcpy(cnxStream.pub_sample_data(), &tmpBuf[outx], args.data_sample_size);
                    outx += args.data_sample_size;
                }
                else {
                    size_t endSpace = rollx - outx;
                    memcpy(cnxStream.pub_sample_data(), &tmpBuf[outx], endSpace);
                    memcpy(cnxStream.pub_sample_data() + endSpace, &tmpBuf[0], args.data_sample_size - endSpace);
                    outx = args.data_sample_size - (uint32_t)endSpace;
                }
                outtot += args.data_sample_size;
                // publish
                while (false == application::shutdown_requested) {
                    try {
                        cnxStream.publish();
                        break;
                    }
                    catch (...) {
                        std::cerr << "Write operation timed out, retrying..." << std::endl;
                    }
                }
            }
        }
    }
    else        // subscriber ======================================
    {
#ifdef WIN32    // open a UDP socket to FFPLAY
        WSADATA wsaData;
        int res = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (res != NO_ERROR) {
            printf("WSAStartup failed with error %d\n", res);
            return;
        }

        destSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (destSocket == INVALID_SOCKET) {
            printf("socket failed with error %d\n", WSAGetLastError());
            WSACleanup();
            return;
        }
        destination.sin_family = AF_INET;
        destination.sin_port = htons(port_base + 1);
        destination.sin_addr.s_addr = inet_addr(hostname.c_str());
#else
        sock = ::socket(AF_INET, SOCK_DGRAM, 0);
        destination.sin_family = AF_INET;
        destination.sin_port = htons(port_base + 1);
        destination.sin_addr.s_addr = inet_addr(hostname.c_str());

        if (connect(sock, (struct sockaddr*)&destination, sizeof(destination)) < 0) {
            std::cout << "UDP Connection error" << std::endl;
        }
#endif
        while (false == application::shutdown_requested) {
            // dispatch the waitset/callback: has any DDS data been received?
            waitset.dispatch(dds::core::Duration(0, 100000));
        }
    }
    // clean up
#ifdef WIN32
    closesocket(destSocket);
    WSACleanup();
#else
    ::close(sock);
#endif
}

/** ----------------------------------------------------------------
 * main()
 * arguments are handled in 'app_helper.hpp'
 **/
int main(int argc, char* argv[])
{
    using namespace application;

    // Parse arguments and handle control-C
    auto arguments = parse_arguments(argc, argv);
    if (arguments.parse_result == ParseReturn::exit) {
        return EXIT_SUCCESS;
    }
    else if (arguments.parse_result == ParseReturn::failure) {
        return EXIT_FAILURE;
    }
    setup_signal_handlers();

    // Sets Connext verbosity to help debugging
    rti::config::Logger::instance().verbosity(arguments.verbosity);

    try {
        participant_main(arguments);
    }
    catch (const std::exception& ex) {
        // This will catch DDS exceptions
        std::cerr << "Exception in participant_main(): " << ex.what() << std::endl;
        return -1;
    }

    // RTI Connext provides a finalize_participant_factory() method
    // if you want to release memory used by the participant factory singleton.
    // Uncomment the following line to release the singleton:
    // dds::domain::DomainParticipant::finalize_participant_factory();

    return 0;
}
