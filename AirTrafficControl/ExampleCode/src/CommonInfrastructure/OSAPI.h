/*********************************************************************************************
(c) 2005-2013 Copyright, Real-Time Innovations, Inc.  All rights reserved.    	                             
RTI grants Licensee a license to use, modify, compile, and create derivative works 
of the Software.  Licensee has the right to distribute object form only for use with RTI 
products.  The Software is provided “as is”, with no warranty of any type, including 
any warranty for fitness for any purpose. RTI is under no obligation to maintain or 
support the Software.  RTI shall not be liable for any incidental or consequential 
damages arising out of the use or inability to use the software.
**********************************************************************************************/

#ifndef OSAPI_H
#define OSAPI_H

// ------------------------------------------------------------------------- //
//
// OS APIs for Windows and Linux
// This file includes the APIs to create threads and mutexes in Linux and
// Windows.
// ------------------------------------------------------------------------- //


#ifdef RTI_WIN32
  /* strtok, fopen warnings */
  #pragma warning( disable : 4996 )
#endif 

#ifdef RTI_WIN32
  #define DllExport __declspec( dllexport )
  #include <Winsock2.h>
  #include <process.h>
#else
  #define DllExport
  #include <sys/select.h>
  #include <semaphore.h>
  #include <pthread.h> 
#endif

#include <string>

// ------------------------------------------------------------------------- //
//
// OS APIs:
// These APIs wrap common OS functionality of creating a thread and mutex.
// These only support Windows and Linux, and are provided as-is.
//
// ------------------------------------------------------------------------- //

// A function that takes a void pointer, and is passed to the thread creation
// function.
typedef void* (*ThreadFunction)(void *);   

// Wrap threads
class OSThread
{

public:
	OSThread(ThreadFunction function, 
		void *functionParam);

	void Run();
private:

#ifdef RTI_WIN32
    HANDLE _thread;
#else 
    pthread_t _thread;
#endif
	ThreadFunction _function;
	void *_functionParam;
};

// Wrap mutexes
class OSMutex
{
public:
	OSMutex();
	~OSMutex();
	void Lock();
	void Unlock();
private:
#ifdef RTI_WIN32
    CRITICAL_SECTION _handleCriticalSection;
#else
	 pthread_mutex_t  _mutex; 
#endif
};


#endif
