#include "TUL_filesystem.h"
#include "TUL_error.h"
#include "TUL_string.h"
#include "TUL_time.h"
#include "TUL_thread.h"

int myfunc(void* data) {
	int failure = TUL_setThreadPriority(TUL_THREAD_PRIORITY_HIGH);
	if(failure) printf("Set priority error: %s\n", TUL_getError());
	printf("%d other thread ID\n", (int) TUL_threadID());
    TUL_sleep(0.5);
    return 5;
}

#include <stdio.h>
int main(int argc, char** argv) {
	printf("created dir: %i\n", TUL_mkdir("test"));
	printf("removed dir: %i\n", TUL_rmdir("test"));
	printf("removed dir: %i\n", TUL_rmdir("test"));
	printf("Error: %s\n", TUL_getError());
	printf("current working directory: %s\n", TUL_getcwd());
	printf("concatenating %s\n", TUL_path_join("abc/def/", "jik"));
	printf("%s and %s is %s\n", "abc", "def", TUL_strjoin("abc","def"));
	double start = TUL_seconds();
	TUL_sleep(0.001);
	printf("%f time has passed\n", TUL_seconds() - start);
	printf("%d current thread ID\n", (int) TUL_threadID());

	TUL_Thread* t = TUL_createThread(&myfunc, "test", NULL);
	printf("%d current thread ID\n", (int) TUL_threadID());
	printf("Waiting for thread..\n");
	int rval = TUL_letThreadFinish(t);
	printf("thread returned: %d\n", rval);

	void* iter = TUL_iterdir_create("othertest/foo");
	const char* path;
	while((path = TUL_iterdir_next(iter))) {
		printf("Content: %s\n", path);
	}
	TUL_iterdir_destroy(iter);

	return 0;
}
