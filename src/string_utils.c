#include "TUL_string.h"
#include "TUL_memory_management.h"
#include <stdlib.h>
#include <string.h>

// Other string utils
// ------------------

const char* TUL_strcopy(const char* source) {
	size_t length = strlen(source) + 1;

	// +1 because strlen doesn't count the trailing \0
	char* rval = (char*) TUL_stringAlloc(length + 1);

	memcpy(rval, source, length+1);
	return rval;
}

const char* TUL_strjoin(const char* first, const char* second) {
	size_t newstrlen = strlen(first) + strlen(second) + 1;

	char* newstr = TUL_stringAlloc(newstrlen);

	// at the beginning of the string, copy the first string without trailing \0
	memcpy(newstr, first, strlen(first));

	// now copy the second string, including its trailing whitespace
	memcpy(&newstr[strlen(first)], second, strlen(second)+1);

	return newstr;
}
