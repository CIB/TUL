/** Module with convenience functions related to time. **/

#include <time.h>

/** Suspend the thread's execution for the given number of seconds. **/
void TUL_sleep(double seconds);

/** Retrieve a time measurement in seconds. This function will internally use
    a high resolution timer where possible, so it is viable for tasks where
    high accuracy is required, such as profiling. **/
double TUL_seconds();

/** Converts a *seconds* measurement as returned by ``TUL_seconds()`` to a timestamp as returned by
    stdlib's ``time()``**/
double TUL_seconds_to_time(time_t reference);

/** Converts a timestamp as returned by stdlib's ``time()`` to a *seconds* measurement as returned by
    ``TUL_seconds``. **/
double TUL_time_to_seconds(double reference);
