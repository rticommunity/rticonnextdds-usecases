/*********************************************************************************************
(c) 2005-2013 Copyright, Real-Time Innovations, Inc.  All rights reserved.    	                             
RTI grants Licensee a license to use, modify, compile, and create derivative works 
of the Software.  Licensee has the right to distribute object form only for use with RTI 
products.  The Software is provided “as is”, with no warranty of any type, including 
any warranty for fitness for any purpose. RTI is under no obligation to maintain or 
support the Software.  RTI shall not be liable for any incidental or consequential 
damages arising out of the use or inability to use the software.
**********************************************************************************************/

#include <iostream>
#include <vector>
#include <sstream>
#include "../Generated/VideoData.h"
#include "../Generated/VideoDataSupport.h"
#include "VideoSubscriberInterface.h"
#include "../CommonInfrastructure/VideoBuffer.h"

using namespace DDS;
using namespace com::media::generated;


// ------------------------------------------------------------------------- //
// The VideoSubscriberInterface is the network interface to the whole application.  This 
// creates DataReaders and DataWriters in order to receive and send data.  
//
// This interface is built from:
// 1. Network data types and topic names defined in the IDL file
// 2. XML configuration files that describe the QoS profiles that should be 
//    used by individual DataWriters and DataReaders.  These describe the 
//    movement and persistence characteristics of the data (how reliable should
//    this be?), as well as other QoS such as resource limits.
// 3. The code itself creates DataReaders and DataWriters, and selects which 
//    profile to use when creating the DataReaders and DataWriters.
//
// For information on the video data type, please see the VideoData.idl
// file.  
//
// For information on the quality of service for streaming video, please
// see the video_stream_multicast.xml file.
//
// Reading video stream data:
// -------------------------
// This class reads video stream data, and displays it.
//
// For information on the video stream data type, please see VideoData.idl
//
// This class receives the video data reliably, but this can be changed in the
// video_stream_multicast.xml file. For more information on the QoS, please 
// see that file.
//
// This class uses a listener to be notified of the arrival of video frames.
// The listener is installed at the time that we create the DataReader.  The 
// listener is notified of frames arriving from within the middleware's queue,
// which is the fastest way to be notified of data arriving. 
// If you reuse this code, BE CAREFUL NOT TO BLOCK inside the 
// on_data_available callback, because you risk losing data.
// ------------------------------------------------------------------------- //

VideoSubscriberInterface::VideoSubscriberInterface( 
							std::vector<std::string>qosFileNames,
							std::string videoMetadata,
							bool multicastVideoStreams)
{ 

	std::string profileName;


	
	// Choose a QoS policy for streaming data, and if you plan to use multicast
	// video data, select a QoS profile that supports multicast streaming data.
	// Note that the QoS profile and QoS library names are constants that are 
	// defined in the .idl file. 
	if (multicastVideoStreams)
	{
		profileName = QOS_PROFILE_MULTICAST_DATA;
	}
	else
	{
		profileName = QOS_PROFILE_STREAMING_DATA;
	}
	_communicator = new DDSCommunicator();

	// Calling the DDSCommunicator class's CreateParticipant method.
	// This creates the DomainParticpant, the first step in creating a DDS
	// application.  This starts the discovery process.  For more information
	// on what the DomainParticipant is responsible for, and how to configure
	// it, see the DDSCommunicator class.
	if (NULL == _communicator->CreateParticipant(0, qosFileNames, 
					QOS_LIBRARY, 
					profileName.c_str())) 
	{
		std::stringstream errss;
		errss << "Failed to create DomainParticipant object";
		throw errss.str();
	}


	// Note that if you want to publish data from this interface,
	// you can do this by calling the DDSCommunicator class's CreatePublisher
	// method. You do _not_ need to create one publisher per DataWriter.


	// Creating a DDS subscriber.  
	// You do _not_ need to create one subscriber per DataReader.
	Subscriber *subscriber = _communicator->CreateSubscriber();
	if (subscriber == NULL) 
	{
		std::stringstream errss;
		errss << "Failed to create Subscriber object";
		throw errss.str();
	}

	// Creating the VideoStreamReader object.
	// We could give the application access to the DataReader directly, but 
	// this simplifies the application's access - in this case, we can choose 
	// to let the application store the data in the DataReader's queue, and 
	// query it directly from the DataReader but we create an object to hide
	// that decision from the user.
	// Initialize the receiver with the QoS profile defined in the 
	// video_stream_multicast.xml file
	_VideoStreamReader = new VideoStreamReader(
		this, 
		subscriber, 
		QOS_LIBRARY,
		profileName.c_str(),
		videoMetadata);

	if (_VideoStreamReader == NULL) 
	{
		std::stringstream errss;
		errss << "Failed to create VideoStreamReader object";
		throw errss.str();
	}

}

// ------------------------------------------------------------------------- //
// Deleting the Video Stream Reader, and the communicator
// infrastructure.  See the individual destructors to see how these are 
// deleted.
VideoSubscriberInterface::~VideoSubscriberInterface()
{

	delete _VideoStreamReader;
	delete _communicator;
}

// ------------------------------------------------------------------------- //
// This creates the DDS Listener that receives updates about video data.
//
// This listener class receives notifications from the middleware's threads
// that data is available.  Note that this means that the users of this 
// listener SHOULD NEVER BLOCK or else risk data loss.  This listener does
// nothing but call the registered event handlers, which means this is the
// responsibility of the event handlers not to block.
void VideoStreamListener::on_data_available(DataReader *reader)
{
	VideoStreamDataReader *videoReader = 
		VideoStreamDataReader::narrow(reader);
	VideoStreamSeq dataSeq;
	SampleInfoSeq infoSeq;
	DDS_ReturnCode_t retCode = DDS_RETCODE_OK;

	if (videoReader == NULL)
	{
		return;	
	}
	while (retCode != DDS_RETCODE_NO_DATA)
	{

		retCode = videoReader->take(dataSeq, infoSeq);

		if ((retCode != DDS_RETCODE_OK) &&
			(retCode != DDS_RETCODE_NO_DATA))
		{
			std::cout << "Error receiving data" << std::endl;
			return;
		}

		for (int i = 0; i < dataSeq.length(); i++)
		{
			if (infoSeq[i].valid_data == DDS_BOOLEAN_TRUE)
			{
				double timestamp = infoSeq[i].source_timestamp.sec + 
						(infoSeq[i].source_timestamp.nanosec / NANOSEC_TO_SEC);

				_reader->NotifyHandlers(&dataSeq[i], dataSeq[i].stream_id, 
					timestamp);
			}
		}

		// Returning the loaned video data to the middleware.  Note that the
		// data was loaned to the application because the application passed an 
		// empty sequence to the take() call.  This is more efficient than 
		// copying the data into a local buffer.
		videoReader->return_loan(dataSeq, infoSeq);
	}


}

// ------------------------------------------------------------------------- //
// This creates the DDS DataReader that receives updates about video frames.
VideoStreamReader::VideoStreamReader(
			VideoSubscriberInterface *comm, 
			Subscriber *sub, 
			const std::string &qosLibrary, 
			const std::string &qosProfile,
			const std::string &videoMetadata) 
{

	if (comm == NULL) 
	{
		std::stringstream errss;
		errss << "VideoStreamReader(): bad parameter \"app\"";
		throw errss.str();
	}

	_communicator = comm;

	// Creating a Topic
	// The topic object is the description of the data that you will be 
	// sending. It associates a particular data type with a name that 
	// describes the meaning of the data.  Along with the data types, and
	// whether your application is reading or writing particular data, this
	// is the data interface of your application.

	// This topic has the name VIDEO_TOPIC - a constant string 
	// that is defined in the .idl file.  (It is not required that you define  
	// your topic name in IDL, but it is a best practice for ensuring the data
	// interface of an application is all defined in one place.)
	// Generally you can register all topics and types up-front if
	// necessary.
	Topic *topic = _communicator->GetCommunicator()->CreateTopic<VideoStream>(
										VIDEO_TOPIC);

	_listener = new VideoStreamListener(this);
	if (_listener == NULL) 
	{
		std::stringstream errss;
		errss << "VideoStreamReader(): failure to create VideoListener.";
		throw errss.str();
	}

	// Setting the user_data QoS:
	// We read the QoS library and profile from the file and then we take that
	// QoS and add the user_data in code.
	// user_data is a QoS that is used to specify data that should be sent 
	// along with discovery.  So, whenever another DomainParticipant discovers
	// this DataReader, it have access to this user_data.

	// In this case, we are using the user_data to send metadata about the
	// video codecs that are being supported.  So, if a remote Video Example
	// Publisher application discovers this application, it will check whether
	// it can provide video that supports the same video codecs that are 
	// supported by the subscribing application.  If they share compatible
	// codecs, it will start publishing video data.
	DDS_DataReaderQos readerQoS;
	DDS_ReturnCode_t retcode = 
		TheParticipantFactory->get_datareader_qos_from_profile(readerQoS,
									qosLibrary.c_str(), qosProfile.c_str());

	readerQoS.user_data.value.from_array(
		reinterpret_cast<const DDS_Octet *>(videoMetadata.c_str()), 
		videoMetadata.length());

	// Creating a DataReader
	// This DataReader will receive the video data, and will store it in its
	// queue, to be retrieved by listener in the on_data_available callback
	 DataReader *reader = sub->create_datareader(topic, 
		readerQoS, _listener, DDS_DATA_AVAILABLE_STATUS);
	if (reader == NULL)
	{
		std::stringstream errss;
		errss << "VideoStreamReader(): failure to create DataReader.";
		throw errss.str();
	}

	 // Down casting to the type-specific reader
	 _reader = VideoStreamDataReader::narrow(reader);

}

// ------------------------------------------------------------------------- //
// Destory the video stream DataReader and WaitSet.  Note that this uses
// the DDS factories that created various objects to later delete them.
VideoStreamReader::~VideoStreamReader()
{

	_reader->delete_contained_entities();
	Subscriber *sub = _reader->get_subscriber();
	sub->delete_datareader(_reader);

}

void VideoStreamReader::RegisterVideoHandler(VideoEventHandler *handler)
{
	_eventHandlers.push_back(handler);
}

void VideoStreamReader::UnregisterVideoHandler(VideoEventHandler *handler)
{
	for (std::vector<VideoEventHandler *>::iterator it = _eventHandlers.begin();
		it != _eventHandlers.end(); it++)
	{
		if ((*it) == handler)
		{
			_eventHandlers.erase(it);
		}
	}
			
}

// ----------------------------------------------------------------------------
//
// Notify handlers of frame events that a frame has arrived
// 
void VideoStreamReader::NotifyHandlers(VideoStream *frame, 
	long streamId, double timestamp)
{
	EMDSBuffer *buffer = NULL;

	for (std::vector<VideoEventHandler *>::iterator it = _eventHandlers.begin();
		it != _eventHandlers.end(); it++)
	{
		DDS_Octet *frameBinaryData = frame->frame.get_contiguous_buffer();

		// Allocate a new buffer
		EMDSBuffer *buffer = new EMDSBuffer(frame->frame.length()); 

		// Copy the data and metadata into the new buffer
		buffer->SetData(frameBinaryData, frame->frame.length());
		buffer->SetSeqn(frame->sequence_number);
		buffer->SetTimestamp(timestamp);

		// If this is not the video end, notify the handler that a new
		// frame update should be processed 
		(*it)->OnFrameUpdate(buffer, streamId);
	}
}



