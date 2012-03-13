#include "TUL_filesystem.h"
#include "TUL_error.h"
#include "TUL_memory_management.h"
#include "TUL_string.h"

/* Code altered from luafilesystem, http://github.com/keplerproject/luafilesystem */

// include the headers required for filesystem functions,
// depending on the system
// ------------------------------------------------------
#ifdef _WIN32
#include <direct.h>
#include <windows.h>
#include <io.h>
#include <stdio.h>
#include <sys/locking.h>
#include <sys/utime.h>
#include <fcntl.h>
#else
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/types.h>
#include <utime.h>
#endif

// --- path_concatenate ---
// ========================
const char* TUL_path_join(const char* first, const char* second) {
	// say first is a/ and second is /b, then we want to join them to a/b, not a//b

	// see if we need to cut a /
	int cut_path_separator = (first[strlen(first) - 1] == '/' && second[0] == '/');

	// if we cut a /, the resulting string will be one character smaller
	// the resulting string length will be the length of the strings, plus 1 for the trailing \0
	int newstrlen = strlen(first) + strlen(second) + 1 - cut_path_separator;
	char* newstr = TUL_stringAlloc(newstrlen);

	// at the beginning of the string, copy the first string without trailing \0
	memcpy(newstr, first, strlen(first));

	// after that, copy the second string, and if we cut a separator, move it one character
	// to the left, in order to overwrite one of the separators with the other

	// also copy second's trailing whitespace
	memcpy(&newstr[strlen(first)-cut_path_separator], second, strlen(second)+1);

	return newstr;
}

// TODO: function to clean up paths

// --- getcwd ---
// ==============
const char* TUL_getcwd() {
  // allocate a string to write the cwd to
  char* rval = TUL_stringAlloc(MAX_PATH);

  // return the allocated string
  return getcwd(rval, MAX_PATH);
}

// --- chdir ---
// =============
int TUL_chdir(const char* path) {
	// the standard chdir already does what we need
	return chdir(path);
}

// --- mkdir ---
// =============
int TUL_mkdir(const char* path) {
	int fail;
#ifdef _WIN32
	fail = _mkdir (path);
#else
	fail =  mkdir (path, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP |
	                     S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH );
#endif
	if (fail) {
		TUL_setError(strerror(errno));
		return 1;
	}
	else {
		return 0; // success!
	}
}

// --- rmdir ---
// =============
int TUL_rmdir(const char* path) {
	int fail;

	fail = rmdir (path);

	if (fail) {
		TUL_setError(strerror(errno));
		return 1;
	}
	else {
		return 0;
	}
}


// ***************** iterdir functions ******************
// ======================================================

// -------------- iterdir struct ---------------
// This struct is used to store the intermediate
// state of a directory iterator.
// =============================================
typedef struct {
	int  closed; // is this iterator done traversing?
#ifdef _WIN32
	long hFile;
	char pattern[MAX_PATH+1];
#else
	DIR *dir;
#endif
} iterdir_data;


// --- iterdir_create ---
// ======================
void* TUL_iterdir_create(const char* path) {
	// create a new iterator
	iterdir_data* iter = (iterdir_data *) TUL_objectAlloc(sizeof(iterdir_data));

	iter->closed = 0;
#ifdef _WIN32
	iter->hFile = 0L;
	// TODO: since the POSIX version breaks already here if the directory can not be opened,
	// test the directory on windows here, too

	// on windows, there's a maximum size for paths that we need to take into account
	if (strlen(path) > MAX_PATH-2) {
		TUL_setError("The given path exceeds the system's path length limit.");
		TUL_objectDealloc(iter);
		return NULL;
	}
	else {
		// TODO: either specifically allow patterns in the path, or somehow filter them out
		sprintf (iter->pattern, "%s/*", path);
	}
#else
	iter->dir = opendir (path);
	if (iter->dir == NULL) {
		TUL_objectDealloc(iter);
		return NULL;
	}
#endif

	return iter;
}

// local inline function used to return strings
inline char* strclone(const char* source) {
	size_t length = strlen(source);

	// +1 because strlen doesn't count the trailing \0
	char* rval = (char*) TUL_stringAlloc(length + 1);
	memcpy(rval, source, length+1);
	return rval;
}

// check if this path should be skipped in the iteration
inline int skip_path(const char* path) {
	return (!strcmp(path, ".") || !strcmp(path, ".."));
}

// --- iterdir_next ---
// ======================
const char* TUL_iterdir_next(void* void_iter) {
	// if the given iter is NULL, probably the creation failed,
	// so just return NULL
	if(void_iter == NULL) {
		return NULL;
	}

// prepare the iterator
// --------------------
	iterdir_data* iter = (iterdir_data*) void_iter;

	// if the iterator has already traversed the dir, do nothing
	if(iter->closed) {
		TUL_setError("The given iterator has already reached the end of the directory.");
		return NULL;
	}

// find the next entry, system-dependent
// -------------------------------------
#ifdef _WIN32
	struct _finddata_t c_file;

	skipEntry: // label used to skip over entries
	if (iter->hFile == 0L) { /* first entry */
		if ((iter->hFile = _findfirst (iter->pattern, &c_file)) == -1L) {
			// there was an error when trying to find the first entry
			iter->closed = 1;
			return NULL;
		} else {
			if(skip_path(c_file.name)) goto skipEntry; // . and .. are useless results, skip!

			// the string needs to be copied, as c_file is on the stack
			return strclone(c_file.name);
		}
	} else { /* next entry */
		if (_findnext (iter->hFile, &c_file) == -1L) {
			/* no more entries => close directory */
			_findclose (iter->hFile);
			iter->closed = 1;
			return NULL;
		} else {
			if(skip_path(c_file.name)) goto skipEntry; // . and .. are useless results, skip!

			// the string needs to be copied, as c_file is on the stack
			return strclone(c_file.name);
		}
	}
#else
	struct dirent *entry;

	if ((entry = readdir (iter->dir)) != NULL) {
		return strclone(entry->d_name);
	} else {
		/* no more entries => close directory */
		closedir (iter->dir);
		iter->closed = 1;
		return NULL;
	}
#endif
}

// --- iterdir_destroy ---
// =======================
void TUL_iterdir_destroy(void* iter) {
	#ifndef _WIN32
		// the directory may still be open, close it!
		if(!closed) closedir(iter->dir);
	#endif
	TUL_objectDealloc(iter);
}
