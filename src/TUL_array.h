/* This module provides basic array functionality, including
   checked accessor functions and resizing.
   
   Array elements are pointers. They can thus be used easily
   with the opaque objects and strings used by TUL.
   
   Note that TUL arrays, like other TUL data structures, are not
   type-safe. The user must ensure that only elements of the
   correct type are inserted into the array.
*/

/** Create a new array with the given initial capacity. **/
void* TUL_array_create(int elements);

/** Destroy the given array, deallocating it. **/
void TUL_array_destroy(void* array);

/** Resize the array, allowing space for up to new_elements.

    Note that like with TUL_realloc, this may invalidate the 
	previous array reference, making it necessary to update it.
**/
void* TUL_array_resize(void* array, int new_elements);

/** Get the array size in elements. **/
int TUL_array_get_size(void* array);

/** Get the object in the array at the specified position.
	
	Returns NULL and sets the error to "Array index out of bounds",
	if the position is out-of-bounds.
 **/
void* TUL_array_get(void* array, int position);

/** Set the object in the array at the specified position.
	
	Returns NULL and sets the error to "Array index out of bounds",
	if the position is out-of-bounds.
 **/
void TUL_array_set(void* array, int position, void* value);

