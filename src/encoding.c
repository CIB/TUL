#include "TUL_encoding.h"
#include "TUL_memory_management.h"
#include "TUL_array.h"
#include "TUL_string.h"
#include <string.h>

// WIN32 implementation
#ifdef _WIN32
#include <windows.h>

const char* TUL_encoding_get_system_codepage() {
	LCID systemLocale = GetSystemDefaultLCID();
	
	char codepageName[128];
	int retrieved = GetLocaleInfo(systemLocale, LOCALE_IDEFAULTANSICODEPAGE, codepageName, 128);
	
	if(retrieved == 0) {
		// TODO: error message
		return 0;
	}
	
	char* rval = TUL_stringAlloc(retrieved+1);
	memcpy(rval, codepageName, retrieved);
	rval[retrieved] = 0;
	
	return rval;
}

const char* TUL_encoding_get_name(const char* encoding) {
	int encodingID = atoi(encoding);
	
	CPINFOEX info;
	
	BOOL result = GetCPInfoEx(encodingID, 0, &info);
	if(!result) return NULL;
	
	const char* rval = TUL_strcopy(info.CodePageName);
	return rval;
}

// Not sure how else to solve this right now, since
// win32 api insists on using a callback function.
// TODO: use a mutex or something to make this thread-safe
static void* array = NULL;
static int arrayPos = -1;
BOOL CALLBACK EnumCodePagesProc(LPTSTR lpCodePageString) {
	if(array == NULL || arrayPos == -1) {
		return 0;
	}
	
	array = TUL_array_resize(array, arrayPos+1);
	TUL_array_set(array, arrayPos, (void*) TUL_strcopy(lpCodePageString));
	arrayPos++;
	
	return 1;
};

const char* TUL_encoding_get_system_codepages() {
	int pos = 0;
	array = TUL_array_create(0);
	arrayPos = 0;
	BOOL success = EnumSystemCodePages(&EnumCodePagesProc, CP_INSTALLED);
	return array;
};

void TUL_encoding_array_destroy(void* array) {
	int arraySize = TUL_array_get_size(array);
	
	int i;
	for(i = 0; i < arraySize; i++) {
		TUL_stringDealloc(TUL_array_get(array, i));
	}
	TUL_array_destroy(array);
}

const char* TUL_encoding_get_utf8() {
	return "utf-8";
}

const char* TUL_encoding_get_utf16() {
	return "utf-16";
}

void* TUL_encoding_convert(void* string, const char* source_encoding, const char* to_encoding) {
	unsigned int sourceEncodingID = atoi(source_encoding);
	unsigned int toEncodingID = atoi(to_encoding);
	
	// the intermediate utf-16 string we'll be using for conversion
	void* intermediate;
	
	// Whether intermediate is separate, and we need to deallocate it later.
	int mustDeallocIntermediate = 0;
	
	// first convert to utf-16
	if(source_encoding != TUL_encoding_get_utf16()) {
		int size = MultiByteToWideChar(sourceEncodingID, 0, string, -1, NULL, 0);
		
		// As we're allocating intermediate, set the flag so we know to deallocate
		// it later(don't need to deallocate it if the source encoding already was
		// utf-16).
		mustDeallocIntermediate = 1;
		intermediate = (void*) TUL_stringAlloc(size * sizeof(wchar_t));
		MultiByteToWideChar(sourceEncodingID, 0, string, -1, intermediate, size);
	} else {
		// if already utf-16, no need to convert
		intermediate = string;
	}
	
	// now convert from utf-16 to target encoding
	void* result;
	if(to_encoding != TUL_encoding_get_utf16()) {
		int size = WideCharToMultiByte(toEncodingID, 0, intermediate, wcslen(intermediate)+2, NULL, 0, NULL, NULL);
		result = (void*) TUL_stringAlloc(size * sizeof(char));
		size = WideCharToMultiByte(toEncodingID, 0, intermediate, wcslen(intermediate), result, size, NULL, NULL);
		
		// No need for the intermediate anymore.
		if(mustDeallocIntermediate) TUL_stringDealloc(intermediate);
	} else {
		result = intermediate;
	}
	
	return result;
}

#endif