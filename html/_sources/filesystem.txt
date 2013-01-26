Filesystem Library
==================

This module is responsible for providing additional functionality in regards to working with the native file system. It is largely inspired by the luafilesystem library.

.. c:function:: char* TUL_getcwd()

	Get the current working directory.

	.. NOTE:: The current working directory(*cwd*) represents your point of reference in the file system. All relative paths will base off the *cwd*.

	.. WARNING:: The returned string is heap allocated and must be manually deallocated, see :ref:`string-allocation`.

.. c:function:: int TUL_chdir(const char* path)

	Changes the current working directory.


.. c:function:: int TUL_mkdir(const char* path)

	Create a new directory at the given path.


.. c:function:: int TUL_rmdir(const char* path)

	Removes the directory at the given path.

	.. NOTE:: The function will fail if the directory at *path* is not empty. To remove a directory and all its contents, you must currently do a manual traversal.

.. c:function:: char* TUL_path_join(const char* first, const char* second)

	Concatenate two paths into one cleanly. This is useful when you have paths that may start/end with a separator, for example *a/* and */b*. With regular string concatenation, that would result in *a//b*, whereas with path_join, you'll get *a/b*.

	.. WARNING:: The returned string is heap allocated and must be manually deallocated, see :ref:`string-allocation`.

iterdir: Directory Traversal
----------------------------

Sometimes it is necessary to traverse all the files in a given directory. This can be done with the *iterdir* set of functions. Use :c:func:`TUL_iterdir_create` to obtain an iterator over a specific directory, then traverse its contents with :c:func:`TUL_iterdir_next` and finally clean up with :c:func:`TUL_iterdir_destroy`.

See also :ref:`opaque-objects`.

.. c:function:: void* TUL_iterdir_create(const char* path)

	Creates an iterator for the contents of a directory, or ``NULL`` on error. Returns an opaque object that can be passed to other *iterdir* functions.

	.. WARNING:: The returned object is heap-allocated and must be deallocated manually with :c:func:`TUL_iterdir_destroy`.

	This iterator will traverse over the direct children of this directory, but not over the children of sub-directories.


.. c:function:: char* TUL_iterdir_next(void* iter)

	Retrieves the next file path in the directory, or ``NULL`` if there's none. The returned path will be relative to the traversed directory.

	.. WARNING:: The returned string is heap allocated and must be manually deallocated, see :ref:`string-allocation`.

	This function can be called on a ``NULL``-iter, so you can attempt to traverse a non-existent or locked directory, and it'll simply be treated as empty.

	Example code: ::

		void* iter = TUL_iterdir_create("foobar");
		char* path;
		while((path = TUL_iterdir_next(iter))) {
			printf("Content: %s\n", path);
		}
		TUL_iterdir_destroy(iter);



.. c:function:: void TUL_iterdir_destroy(void* iter)

	Destroys the iterator, this must be called to avoid a memory leak.
