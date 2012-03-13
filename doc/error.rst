Error Handling
==============

Basic error handling functionality. A LWCL library will set the current error with :c:func:`lwcl_seterror`, and the user can retrieve it with :c:func:`lwcl_geterror`.

.. c:member:: #define LWCL_MAX_ERROR_SIZE

	A macro defining the maximum size in bytes for error messages. Should be an integer value large enough to hold any potential error being raised.

.. c:function:: const char* lwcl_geterror()

	Get the last error raised, or ``NULL`` if the error is cleared.

.. c:function:: void lwcl_seterror(const char* error)

	Set the last error raised.

.. c:function:: void lwcl_clearerror()

	Clear the last error raised. Any subsequent call to :c:func:`lwcl_geterror` will return ``NULL``.