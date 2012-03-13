#include "TUL_error.h"
#include <stdlib.h>
#include <string.h>

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
