#include "TUL_array.h"
#include "TUL_memory_management.h"

typedef struct {
	int size;
	void* elements[];
} _array;

void* TUL_array_create(int elements) {
	_array* rval = (_array*) TUL_objectAlloc(sizeof(_array) + sizeof(void*) * elements);
	rval->size = elements;
	memset(&rval->elements, 0, sizeof(void*) * elements);
	return rval;
}

void TUL_array_destroy(void* array) {
	TUL_objectDealloc(array);
}

void* TUL_array_resize(void* array, int new_elements) {
	_array* rval = (_array*) TUL_realloc(array, sizeof(_array) + sizeof(void*) * new_elements);
	rval->size = new_elements;
	return (void*) rval;
}

int TUL_array_get_size(void* in) {
	_array* array = (_array*) in;
	return array->size;
}

void* TUL_array_get(void* in, int position) {
	_array* array = (_array*) in;
	
	if(position < 0 || position >= array->size) {
		return NULL;
	}
	
	return array->elements[position];
}

void TUL_array_set(void* in, int position, void* value) {
	_array* array = (_array*) in;
	
	if(position < 0 || position >= array->size) {
		return;
	}
	
	array->elements[position] = value;
}

