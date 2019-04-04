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
#include "VideoPublisherInterface.h"


using namespace com::media::generated;

// ----------------------------------------------------------------------------
// The VideoPublisherInterface is the network interface to the whole 
// application.  This creates a DataWriter in order to send video stream data
// over the network (or shared memory) to other applications that are 
// interested in video streams.
//
// This interface is built from:
// 1. Network data types and topic names defined in the IDL file
// 2. XML configuration files that describe the QoS profiles that should be 
//    used by individual DataWriters and DataReaders.  These describe the 
//    movement and persistence characteristics of the data (how reliable should
//    this be?), as well as other QoS such as resource limits.
// 3. The code itself creates DataWriters, and selects which QoS profile to use
//    when creating the DataWriters.
// 
// Writing video stream data:
// -------------------------
// This application sends video stream data, configured to act as streaming data
// This will reliably deliver the video stream to both existing and late-joining 
// applications that subscribe to video stream data.  Late joining applications 
// will not receive all video frames from the beginning, but will start 
// receiving frames in the middle of the stream.
//
// For information on the video stream data type, please see the 
// VideoData.idl file.  
//
// For information on the quality of service for video stream data, please
// see the video_stream_multicast.xml file.
//
// Listening to discovery data:
// ----------------------------
// This application listens to the discovery data that the RTI Connext DDS 
// middleware uses to discover remote DomainParticipants, DataWriters, and
// DataReaders.  This listens just to the DataReader traffic to see if 
// there is a remote DataReader that:
//   1) Has the same topic
//   2) Has been configured with USER_DATA QoS.  This USER_DATA QoS is 
//      metadata that is sent as part of discovery.
//   3) Has codec information in that USER_DATA that is compatible with the
//      codecs that this application can stream.
//   
// If this application discovers a remote DataReader with no USER_DATA, or
// with a codec that this does not support, it uses the ignore() API to avoid
// sending data to that DataReader.
//
// ------------------------------------------------------------------------- //

VideoPublisherInterface::VideoPublisherInterface(
			std::vector<std::string> xmlFiles,
			CodecCompatibleHandler *codecCompatibilityHandler) 
{

	_communicator = new DDSCommunicator();

	// Create a discovery listener
	// This will listen to discovery information and will call back the 
	// codecCompatibilityHandler.  The codecCompatibilityHandler will 
	// query the video framework to see if the remote DataReader's codec is
	// compatible with the codec we are publishing.
	VideoPublisherDiscoveryListener *discoveryListener = 
		new VideoPublisherDiscoveryListener(codecCompatibilityHandler);

	// Create a DomainParticipant
	// Start by creating a DomainParticipant.  Generally you will have only
	// one DomainParticipant per application.  A DomainParticipant is
	// responsible for starting the discovery process, allocating resources,
	// and being the factory class used to create Publishers, Subscribers, 
	// Topics, etc.
	// Note that the QoS profile and QoS library names are constants that are 
	// defined in the .idl file. 
	if (NULL == _communicator->CreateParticipant(0, xmlFiles, 
				QOS_LIBRARY, QOS_PROFILE_STREAMING_DATA,
				discoveryListener, DATAREADER_DISCOVERY_KIND)) 
	{
		std::stringstream errss;
		errss << "Failed to create DomainParticipant object";
		throw errss.str();
	}

	// Create a Publisher
	// This application only writes data, so we only need to create a
	// publisher.  
	// Note that one Publisher can be used to create multiple DataWriters
	DDS::Publisher *pub = _communicator->CreatePublisher();

	if (pub == NULL) 
	{
		std::stringstream errss;
		errss << "Failed to create Publisher object";
		throw errss.str();
	}


	// Creating a Topic
	// The Topic object is the description of the data that you will be 
	// sending. It associates a particular data type with a name that 
	// describes the meaning of the data.  Along with the data types, and
	// whether your application is reading or writing particular data, this
	// is the data interface of your application.

	// This topic has the name VIDEO_TOPIC - a constant  
	// string that is defined in the .idl file.  (It is not required that
	// you define your topic name in IDL, but it is a best practice for
	// ensuring the data interface of an application is all defined in one 
	// place. You can register all topics and types up-front, if you nee
	DDS::Topic *topic = _communicator->CreateTopic<VideoStream>( 
		VIDEO_TOPIC);

	// Create a DataWriter.  
	// This creates a single DataWriter that writes video stream data, with QoS
	// that is used for streaming data.

	// Choose a QoS policy for streaming data (the choice to use multicast is
	// decided by the DataReader, not the DataWriter)
	// Note that the QoS profile and QoS library names are constants that are 
	// defined in the .idl file. 
	DDS::DataWriter *writer = pub->create_datawriter_with_profile(topic, 
		QOS_LIBRARY, QOS_PROFILE_STREAMING_DATA, 
		NULL, DDS_STATUS_MASK_NONE);

	// Downcast the generic datawriter to a video stream DataWriter 
	_writer = VideoStreamDataWriter::narrow(writer);

	if (_writer == NULL) 
	{
		std::stringstream errss;
		errss << 
			"VideoPublisherInterface(): failure to create writer. "
			"Inconsistent Qos?";
		throw errss.str();
	}

}

// ----------------------------------------------------------------------------
// Destructor.
// Deletes the DataWriter, and the Communicator object
VideoPublisherInterface::~VideoPublisherInterface()
{
	DDS::Publisher *pub = _writer->get_publisher();
	pub->delete_datawriter(_writer);
	_writer = NULL;

	delete _communicator;
}


// ----------------------------------------------------------------------------
// Sends the videos tream over a transport (such as shared memory or UDPv4)
bool VideoPublisherInterface::Write(DdsAutoType<VideoStream> data)
{
	DDS_ReturnCode_t retcode = DDS_RETCODE_OK;
	DDS_InstanceHandle_t handle = DDS_HANDLE_NIL;

	// This actually sends the video data over the network.  
	retcode = _writer->write(data, handle);

	if (retcode != DDS_RETCODE_OK) 
	{
		return false;
	}

/*	cout << "Writing sample #" << data.equence_number
		<< ", length: " << data.frame.length() << endl;*/

	return true;

}

// ----------------------------------------------------------------------------
// Sends a deletion message for the streaming video data over a transport (such 
// as shared memory or UDPv4) This uses the unregiste_instance call to notify
// other applications that this video stream has ended
bool VideoPublisherInterface::Delete(DdsAutoType<VideoStream> data)
{
	DDS_ReturnCode_t retcode = DDS_RETCODE_OK;
	DDS_InstanceHandle_t handle = DDS_HANDLE_NIL;

	// Note that the deletion maps to an "unregister" in the RTI Connext
	// DDS world.  This allows the instance to be cleaned up entirely, 
	// so the space can be reused for another instance.  If you call
	// "dispose" it will not clean up the space for a new instance - 
	// instead it marks the current instance disposed and expects that you
	// might reuse the same instance again later.
	retcode = _writer->unregister_instance(data, handle);

	if (retcode != DDS_RETCODE_OK)
	{
		return false;
	}

	return true;
}

// ----------------------------------------------------------------------------
// This is a listener callback that is called from an RTI Connext DDS 
// middleware thread.  It is called when the local DomainParticipant discovers
// a remote DataReader.
// 
// What this does:
//   1. Check if the DataReader is reading the Topic that this application is
//      writing
//   2. Check if the (remote) DataReader has used the user_data QoS to send 
//      metadata about the codec(s) it supports.
//   3. If the (remote) DataReader does not have applicable codecs, ignore it.
//
void VideoPublisherDiscoveryListener::on_data_available(DDSDataReader *reader)
{
	// Cast the DataReader passed into this callback to a 
	// "SubscriptionBuiltinTopicDataDataReader" that gets notifications about
	// remote DataReaders.
	DDS::SubscriptionBuiltinTopicDataDataReader *builtin_reader =
		(DDS::SubscriptionBuiltinTopicDataDataReader*) reader;
	DDS_SubscriptionBuiltinTopicDataSeq data_seq;
	DDS_SampleInfoSeq info_seq;
	DDS_ReturnCode_t retcode;

	// Used to retrieve the metadata that was stored in the user_data Qos to
	// send as part of discovery.
	char *readerData;
    
	// We only process newly seen participants
	retcode = builtin_reader->take(data_seq, info_seq, DDS_LENGTH_UNLIMITED, 
		DDS_ANY_SAMPLE_STATE, DDS_NEW_VIEW_STATE, 
		DDS_ANY_INSTANCE_STATE);

	// It is unlikely that we will be notified if there is nodata, but we do
	// not treat it as an error.
	if (retcode == DDS_RETCODE_NO_DATA)
	{	
		return;
	}

	if (retcode != DDS_RETCODE_OK) 
	{
		std::cout << "Error: failed to access data from the built-in reader" 
			<< std::endl;
		return;
	}

	// Iterate over all the notifications we have received about new
	// DataReaders that we have discovered.
	for(int i = 0; i < data_seq.length(); ++i) 
	{
		// Having valid_data = false is a normal scenario if we are receiving
		// a notification that a DataReader was shut down.
		if (!info_seq[i].valid_data)
		{
			continue;
		}

		// If I have discovered a DataReader that is not reading the same 
		// video topic that this application is writing, do not bother
		// to check whether that DataReader has metadata.
		if (0 != strcmp(data_seq[i].topic_name, VIDEO_TOPIC))
		{
			continue;
		}

		readerData = NULL;

		bool isCompatible = false;

		// see if there is user_data associated with the DataReader
		if (data_seq[i].user_data.value.length() != 0) 
		{
			// This sequence is guaranteed to be contiguous
			readerData = (char*)&data_seq[i].user_data.value[0];

			// Call back the handler (which will call the video 
			// infrastructure) to find out if the remote codec is compatible
			// with the codecs this application is publishing.
			isCompatible = _handler->CodecsCompatible(readerData);

		}
		
		if (!isCompatible) 
		{
			// Will not write to this DataReader.  Using the ignore() 
			// API to ignore the participant and 
			std::cout << "Discovered a DataReader with an incompatible codec. "
				<< "Ignoring it (not sending it any data)" << std::endl;
			DDSDomainParticipant *participant =
				reader->get_subscriber()->get_participant();
			retcode = participant->ignore_subscription(info_seq[i].instance_handle);
			if (retcode != DDS_RETCODE_OK) 
			{
				std::cout << "Error ignoring participant: " << retcode << std::endl;
				return;
			}
		}
	}
	
	// Returning the loaned discovery data to the middleware.  Note that the
	// data was loaned to the application because the application passed an 
	// empty sequence to the take() call.  This is more efficient than 
	// copying the data into a local buffer.
	builtin_reader->return_loan(data_seq, info_seq);

}

