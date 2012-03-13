Time
====

This module extends the standard ``<ctime.h>`` with additional functionality that is commonly used.

.. c:function:: void TUL_sleep(double seconds)

	Suspend the thread's execution for the given duration in *seconds*. On Windows, this has a millisecond accuracy.


.. c:function:: double TUL_seconds()

	Retrieve a high-accuracy time measurement in seconds.

	.. NOTE:: This is not an absolute time-measurement, it can't be used to store a date after the process exits. For those purposes, use :c:func:`TUL_seconds_to_time` to retrieve a standard ``time_t`` timestamp.

	This function will internally use a high resolution timer where possible, so it is suitable for tasks where high accuracy is required, for instance profiling.


.. c:function:: time_t TUL_seconds_to_time()

	Converts a *seconds* measurement as returned by :c:func:`TUL_seconds` to a timestamp as returned by stdlib's ``time()``


.. c:function:: double TUL_time_to_seconds()

	Converts a timestamp as returned by stdlib's ``time()`` to a *seconds* measurement as returned by :c:func:`TUL_seconds`.
