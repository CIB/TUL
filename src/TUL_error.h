/* Very simple error handling. Write and retrieve error strings. */

#define TUL_MAX_ERROR_SIZE 1024

/** Get the last error raised, or NULL if none. **/
const char* TUL_getError();

/** Set the last error raised. **/
void TUL_setError(const char* error);

/** Clear the last error raised. **/
void TUL_clearError();
