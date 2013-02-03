#include <string.h>
#include <stdlib.h>

/** This module represents an abstraction layer for any memory allocation happening in LWCL.
	Note that if you're only interested in the objects that are returned, you only need to
	change the memory handlers for opaque objects and strings.
**/

// Simple malloc/realloc/free wrappers
// -----------------------------------
static inline void* TUL_malloc(size_t size) {
	return malloc(size);
}

static inline void* TUL_realloc(void* ptr, size_t size) {
	return realloc(ptr, size);
}

static inline void TUL_free(void* ptr) {
	free(ptr);
}

// Specialized allocation functions for LWCL types.
// ------------------------------------------------

/** Allocate an opaque object with the given size. **/
static inline void* TUL_objectAlloc(size_t size) {
	return TUL_malloc(size);
}

/** Deallocate an opaque object. **/
static inline void TUL_objectDealloc(void* object) {
	TUL_free(object);
}

/** Allocate a \0-terminated string, size must include space for
	the trailing \0.
**/
static inline char* TUL_stringAlloc(size_t size) {
	return (char*) TUL_malloc(size);
}

/** Deallocate a \0-terminated string. **/
static inline void TUL_stringDealloc(const char* string) {
	return TUL_free((void*) string);
}
