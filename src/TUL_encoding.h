/** A thin wrapper around the system codepage library.
    
	Encodings are stored as strings. Note that different
	systems(e.g. linux and windows) use different names
	for the same encoding, and this module currently
	makes no effort to standardize them.
**/

/** Returns the encoding used by the system. **/
const char* TUL_encoding_get_system_codepage();

/** Returns the encoding representing UTF8. **/
const char* TUL_encoding_get_utf8();

/** Returns the encoding representing UTF16. **/
const char* TUL_encoding_get_utf16();

/** Returns the encoding representing UTF32. **/
const char* TUL_encoding_get_utf32();

/** Returns a TUL_array of encodings installed on the system. **/
const char* TUL_encoding_get_system_codepages();

/** Deallocates an entire array of encodings, as returned by
    by TUL_encoding_get_system_codepage.
	
	Note that this will deallocate all strings contained in
	the array. If you want to keep a reference to any of the
	encodings contained in the array, copy it out first using
	TUL_strcopy.
**/
void TUL_encoding_array_destroy(void* array);

/** Copies a codepage. **/
void TUL_encoding_copy(const char* encoding);

/** Destroys a single codepage, deallocating it. **/
void TUL_encoding_destroy(const char* encoding);

/** Returns the name of an encoding. Note that these, too, are
    not standardized among systems.
**/
const char* TUL_encoding_get_name(const char* encoding);

/** Converts a string from one encoding into the other.
	
	Source and target character type(e.g. char or wchar) depend on source
	and target encoding and will be converted automatically.
 **/
void* TUL_encoding_convert(void* string, const char* source_encoding, const char* to_encoding);