/** Simple string utilities to work with C strings.
	Also includes functions for the LWCL temporary string stack.
**/

#include <string.h>

/** Copies a string into new memory, allocated with TUL_malloc. **/
const char* TUL_strcopy(const char* source);

/** Creates a new string by concatenating two existing strings. **/
const char* TUL_strjoin(const char* first, const char* second);
