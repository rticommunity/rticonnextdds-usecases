#include "../CommonInfrastructure/OSAPI.h"

OSThread::OSThread(
	ThreadFunction function, 
	void *functionParam)
{
	_function = function;
	_functionParam = functionParam;
}

void OSThread::Run()
{

#ifdef RTI_WIN32
    _thread = (HANDLE) _beginthread(
		(void(__cdecl*)(void*))_function,
        0, (void*)_functionParam);
#else
    pthread_attr_t threadAttr;
    pthread_attr_init(&threadAttr);
    pthread_attr_setdetachstate(&threadAttr, PTHREAD_CREATE_JOINABLE);
    error = pthread_create(
                &_thread, 
                &threadAttr, 
                _function,
                (void *)_functionParam);
    pthread_attr_destroy(&threadAttr);
  #endif
}

OSMutex::OSMutex()
{
#ifdef RTI_WIN32
	InitializeCriticalSection(&_handleCriticalSection);
#else
	pthread_mutex_init(&_mutex, NULL);
#endif
}

OSMutex::~OSMutex()
{
#ifdef RTI_WIN32
	DeleteCriticalSection(&_handleCriticalSection);
#else
	pthread_mutex_destroy(_mutex);
#endif
}

void OSMutex::Lock()
{
#ifdef RTI_WIN32
        EnterCriticalSection(&_handleCriticalSection);
#else
	pthread_mutex_lock(&_mutex);
#endif


}

void OSMutex::Unlock()
{
#ifdef RTI_WIN32
	LeaveCriticalSection(&_handleCriticalSection);
#else
	pthread_mutex_unlock(&_mutex);
#endif
}

