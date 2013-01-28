#include "TUL_error.h"
#include <stdlib.h>
#include <string.h>

#ifdef TUL_THREADING
// If threading is enabled, error handling
// needs to be thread-safe.

#include "SDL_error.h"

const char* TUL_getError() {
    return SDL_GetError();
}

void TUL_setError(const char* error) {
    SDL_SetError(error);
}

void TUL_clearError() {
	SDL_ClearError();
}

#else

// If threading is disabled, simply use a static variable.
#define __TUL_maxErrorSize 1024
char __TUL_error[__TUL_maxErrorSize] = { 0 };
char __TUL_largeError[] = "Error message to large for display.";

const char* TUL_getError() {
    return __TUL_error;
}

void TUL_setError(const char* error) {
    // If the error message is too large, instead use an error message
    // stating that the message was too large.
    if(strlen(error) > __TUL_maxErrorSize) {
        memcpy(__TUL_error, __TUL_largeError, sizeof(__TUL_largeError));
    } else {
        memcpy(__TUL_error, error, strlen(error) + 1);
    }
}
#endif
