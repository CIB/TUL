Threading
=========

This module is responsible for managing threads, and threading-related concepts such as mutexes. It is currently just a thin wrapper around the SDL thread library, which is a solid cross-platform threading API. See http://wiki.libsdl.org/moin.cgi/CategoryThread for details.

.. c:function:: unsigned long TUL_threadID()

	Returns a unique identifier for the current running thread. 


.. c:function:: unsigned long TUL_threadToID(TUL_Thread* thread)

	Retrieve a unique identifier from a specific thread object.


.. c:function:: TUL_Thread* TUL_createThread(int (*threadFunc)(void* data), const char* name, void* data)
	
	Creates a new thread and runs it immediately with the given function pointer.

    A function pointer in this case is unavoidable, because there's no other way to give the thread a function to run.
	
    .. NOTE:: The thread will automatically be deallocated when the callback function finishes. It's thus not necessary to manually deallocate the returned opaque object.


.. c:function:: int TUL_setThreadPriority(int priority)

	Set the priority of the thread. Low priority threads are more likely to be interrupted by higher priority threads.

	*priority* must be one of the following constants.

	===========================  =====
	Constant                     Value  
	===========================  =====
	TUL_THREAD_PRIORITY_LOW      ``0``
	TUL_THREAD_PRIORITY_NORMAL   ``1``
	TUL_THREAD_PRIORITY_HIGH     ``2``
	===========================  =====

	.. NOTE:: On some systems, high priority threads are not available to all users.

	
.. c:function:: int TUL_letThreadFinish(TUL_Thread* thread)

	This will cause the current thread to suspend execution until the given thread has finished.

	The return value is that of the ``threadFunc`` that was passed to :c:func:`TUL_createThread` .
