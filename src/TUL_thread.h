/** This module is responsible for managing threads, and threading-related concepts such as mutexes.
    It is currently just a thin wrapper around the SDL thread utils.
*/

// SDL documentation: http://wiki.libsdl.org/moin.cgi/CategoryThread

/** An opaque object type. **/
typedef struct _TUL_THREAD TUL_Thread;

/** Returns a unique identifier for the current running thread. **/
unsigned long TUL_threadID();

/** Retrieve threadID from a specific thread object. **/
unsigned long TUL_threadToID(TUL_Thread* thread);

/** Creates a new thread and starts it immediately with the given function pointer.

    A function pointer in this case is unavoidable, because there's no other way to give
    the thread a function to run.

    .. NOTE:: The thread will automatically be deallocated when the callback function finishes.
              It's thus not necessary to manually deallocate the returned opaque object.
**/
TUL_Thread* TUL_createThread(int (*threadFunc)(void* data), const char* name, void* data);

static const int TUL_THREAD_PRIORITY_LOW = 0;
static const int TUL_THREAD_PRIORITY_NORMAL = 1;
static const int TUL_THREAD_PRIORITY_HIGH = 2;

/** Set the priority of the thread. Low priority threads are more likely to be interrupted by higher priority threads.
    *priority* must be one of the ``TUL_THREAD_PRIORITY_*`` constants.

    .. NOTE:: On some systems, high priority threads are not available to all users.
**/
int TUL_setThreadPriority(int priority);

/** This will cause the current thread to suspend execution until the given thread has finished.

    This will return the same value that is returned by the ``threadFunc`` that was passed to :c:func:`TUL_createThread`.
**/
int TUL_letThreadFinish(TUL_Thread* thread);
