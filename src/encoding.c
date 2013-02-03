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

#include <stdio.h>

const char* TUL_encoding_get_name(const char* encoding) {
	int encodingID = atoi(encoding);
	
	CPINFOEX info;
	
	BOOL result = GetCPInfoEx(encodingID, 0, &info);
	if(!result) return TUL_strcopy(encoding);
	
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
		return;
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

#endif