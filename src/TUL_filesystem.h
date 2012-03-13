/* This module is responsible for providing additional functionality
   in regards to working with the native file system.

   It is largely inspired by the luafilesystem library.
*/

/** Concatenate two paths into one cleanly. **/
const char* TUL_path_join(const char* first, const char* second);

/** Get the current working directory. **/
const char* TUL_getcwd();

/** Change the current working directory, that is, navigate the filesystem. **/
int TUL_chdir(const char* path);

/** Create a new directory at the given path. **/
int TUL_mkdir(const char* path);

/** Removes the directory at the given path. The directory has to be empty. **/
int TUL_rmdir(const char* path);

/** Creates an iterator for the contents of a directory, or NULL on error. **/
void* TUL_iterdir_create(const char* path);

/** Retrieves the next file path in the directory, or NULL if there's none.**/
const char* TUL_iterdir_next(void* iter);

/** Destroys an iterator, internally free's the memory. **/
void TUL_iterdir_destroy(void* iter);
