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
	const char* rval = TUL_strcopy(info.CodePageName);
	return rval;
}

#endif