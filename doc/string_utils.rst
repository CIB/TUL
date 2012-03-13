String Utils
============

Simple string utilities to work with C strings.

.. c:function:: const char* TUL_strcopy(const char* source)

	Creates a new copy of the given C string. The string must be ``\0``-terminated.

	.. WARNING:: The returned string is heap allocated and must be manually deallocated, see :ref:`string-allocation`.

.. c:function:: const char* TUL_strjoin(const char* first, const char* second)

	Creates a new string by concatenating two existing strings.

	.. WARNING:: The returned string is heap allocated and must be manually deallocated, see :ref:`string-allocation`.
