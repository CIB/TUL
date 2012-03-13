Memory Management
=================

Abstraction layer for the methods through which LWCL handles memory. You are encouraged to change functions in *memory_management.h* directly, in order to employ your project's individual memory management strategy.

There are only two distinct datatypes that LWCL will ever allocate itself and return to you.

================    ======   ========================================  ======================================================================
Datatype            C-Type   Allocate With                             Deallocate With
================    ======   ========================================  ======================================================================
String              char*    :c:func:`TUL_stringAlloc`                 :c:func:`TUL_stringDealloc`
Opaque Object       void*    Type-specific handler(``TUL_*_create``)   Type-specific handler(``TUL_*_destroy``)
================    ======   ========================================  ======================================================================

.. _string-allocation:

String Allocation
-----------------

Sometimes it's necessary for LWCL to return newly created strings to the caller. These are allocated with :c:func:`TUL_stringAlloc`, which by default uses standard system ``malloc``. This means that strings returned by LWCL functions must be manually deallocated with :c:func:`TUL_stringDealloc`, or otherwise memory leaks will occur.

.. NOTE:: You can expect any LWCL function that returns ``char*`` to return strings allocated with :c:func:`TUL_stringAlloc`, unless explicitly stated otherwise.

Consider the following code ::

	const char* printCWD() {
		const char* cwd = TUL_getcwd();
		printf(cwd);
		return;
	}

As you can see, a newly allocated string is retrieved with the call to ``TUL_getcwd()``. However, a memory leak is caused, because the reference to the string is discarded without removing the string itself, making it impossible to deallocate it. In order to implement this function properly, the string reference has to be discarded before the function exits! ::

	const char* printCWD() {
		const char* cwd = TUL_getcwd();
		printf(cwd);
		TUL_stringDealloc(cwd);
		return;
	}

This may seem like a hassle, but it is quite a natural way to treat strings in C. If your language has a garbage collector or reference counting, you can easily copy or wrap the string into such a mechanism.

.. _opaque-objects:

Opaque Objects
--------------

Since LWCL does not expose any struct objects directly in its API, *custom objects* are represented to the user as a mere pointer(``void*``). These will internally be allocated and deallocated with :c:func:`TUL_objectAlloc` and :c:func:`TUL_objectDealloc`, but a user should **not** call these functions directly outside a LWCL library. Instead, objects should be created and destroyed with the ``TUL_*_create`` and ``TUL_*_destroy`` set of functions.

Opaque objects are not type-safe; they do not store a reference to their own type. The user is responsible for this. LWCL functions that take an opaque object should never be called with the wrong type of opaque object.

Memory Management Functions
---------------------------

The following set of functions is just a wrapper around the standard malloc family. It's here so that a user can choose to replace system malloc with something else.

.. c:function:: void* TUL_malloc(size_t size)

.. c:function:: void* TUL_realloc(void* ptr, size_t size)

.. c:function:: void TUL_free(void* ptr)


These functions are used for object and string allocation. They may be changed in order to better fit the memory management model of a user.

.. c:function:: void* TUL_objectAlloc(size_t size)

	Allocate an opaque object with the given *size* and return a pointer.


.. c:function:: void TUL_objectDealloc(void* object)

	Deallocate the opaque *object*.


.. c:function:: char* TUL_stringAlloc(size_t size)

	Allocate a \0-terminated string with the given *size* in memory.

	The size must include the terminating \0, so *size* must be strlen(string) + 1

.. c:function:: char* TUL_stringDealloc(char* string)

	Deallocate the \0-terminated *string*.
