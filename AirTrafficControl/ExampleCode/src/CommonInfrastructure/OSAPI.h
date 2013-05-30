
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
typedef void (*ThreadFunction)(void *);   

// wrap
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