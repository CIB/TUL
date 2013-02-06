Encoding
========

This library represents a thin wrapper around system functionality to work with encodings and codepages. An encoding is a mapping from the binary data in a string, to individual glyphs or characters. See `Joel's blog <http://www.joelonsoftware.com/articles/Unicode.html>`_ for more information on the subject.
    
Encoding identifiers are stored as strings.

.. WARNING:: Neither encoding identifiers, nor encoding names are currently standardized across systems. It is recommended to only use and store them locally.

.. c:function:: const char* TUL_encoding_get_system_codepage()

	Returns the encoding used by the system.
	
	.. WARNING:: The returned string is heap allocated and must be manually deallocated, see :ref:`string-allocation`.

	
.. c:function:: const char* TUL_encoding_get_utf8()

	Returns the identifier that represents UTF-8 on this system.
	
	
.. c:function:: const char* TUL_encoding_get_utf16()

	Returns the identifier that represents UTF-16 on this system.
	
.. c:function:: void* TUL_encoding_get_system_codepages()

	Returns a TUL_array of encodings installed on the system.
	
	.. WARNING:: The returned array and its contents are heap allocated. You can deallocate them conveniently using :c:func:`TUL_encoding_array_destroy`.
	
	
.. c:function:: void* TUL_encoding_array_destroy()

	Deallocates an array as returned by :c:func:`TUL_encoding_get_system_codepages`, including each contained string.
	
	.. WARNING:: This will deallocate each string contained in the array. If you wish to keep references to any of the retrieved encodings after deallocating the array, use :c:func:`TUL_strcopy` to get an independent copy.
	
	
.. c:function:: const char* TUL_encoding_get_name(const char* encoding)

	Returns a human-readable description of an encoding, or NULL if the encoding has no associated name. 
	
	.. NOTE:: At least on windows, there are usually quite a few codepages installed that have no associated name. You should thus always handle the possibility of encodings without name, for example by ignoring them, or by using their ID as their name.

	
.. c:function:: void* TUL_encoding_convert(void* string, const char* source_encoding, const char* to_encoding)
	
	Converts a string from one encoding into the other.
	
	Source and target character type(e.g. char or wchar) depend on source and target encoding and will be converted automatically.
	
	.. WARNING:: The returned string is heap allocated and must be manually deallocated, see :ref:`string-allocation`.