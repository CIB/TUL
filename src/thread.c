/** Simply wrap the SDL functions up. **/

#include "TUL_thread.h"
#include "SDL_thread.h"

unsigned long TUL_threadID() {
    return SDL_ThreadID();
}

unsigned long TUL_threadToID(TUL_Thread* thread) {
    return SDL_GetThreadID((SDL_Thread*) thread);
}

TUL_Thread* TUL_createThread(int (*threadFunc)(void* data), const char* name, void* data) {
    return (TUL_Thread*) SDL_CreateThread(threadFunc, name, data);
}

int TUL_setThreadPriority(int priority) {
    return SDL_SetThreadPriority(priority);
}

int TUL_letThreadFinish(TUL_Thread* thread) {
    int rval = -1;
    SDL_WaitThread((SDL_Thread*) thread, &rval);
    return rval;
}
