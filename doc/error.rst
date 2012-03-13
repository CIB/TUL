Error Handling
==============

Basic error handling functionality. A LWCL library will set the current error with :c:func:`lwcl_seterror`, and the user can retrieve it with :c:func:`lwcl_getError`.

.. c:member:: #define LWCL_MAX_ERROR_SIZE

	A macro defining the maximum size in bytes for error messages. Should be an integer value large enough to hold any potential error being raised.

.. c:function:: const char* lwcl_getError()

	Get the last error raised, or ``NULL`` if the error is cleared.
	
	.. NOTE:: The string returned by this function is a reference to internal memory. It need not be manually deallocated, but the reference becomes invalid on the next call to a ``TUL_*`` function.

.. c:function:: void lwcl_setError(const char* error)

	Set the last error raised.

.. c:function:: void lwcl_clearError()

	Clear the last error raised. Any subsequent call to :c:func:`lwcl_geterror` will return ``NULL``.