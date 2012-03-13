#include "TUL_time.h"
#include "TUL_error.h"

#ifdef _WIN32
    #include <windows.h>
#endif

double TUL_seconds() {
    // get a high resolution time through system-specific methods
    #ifdef _WIN32
        // retrieve the high resolution counter ticks
        LARGE_INTEGER counter, frequency;
        if(!QueryPerformanceCounter(&counter)) {
            TUL_setError("WIN32 Error: Failed to retrieve high resolution time.");
            return 0x7ff0000000000000; // INFINITY
        }
        if(!QueryPerformanceFrequency(&frequency)) {
            TUL_setError("WIN32 Error: Failed to retrieve high resolution time.");
            return 0x7ff0000000000000; // INFINITY
        }

        // convert the ticks to a seconds value as double
        double rval = counter.QuadPart;
        rval /= frequency.QuadPart;

        return rval;
    #endif

    // TODO: POSIX implementation
}

void TUL_sleep(double seconds) {
    #ifdef _WIN32
        // WIN32 Sleep takes milliseconds, so just convert the number
        Sleep((DWORD) (seconds * 1000));
    #endif
}

double TUL_seconds_to_time(time_t reference) {
    time_t now = time(NULL);
    double seconds_now = TUL_seconds();

    double seconds_passed = now - reference;

    return seconds_now - seconds_passed;
}

double TUL_time_to_seconds(double reference) {
    time_t now = time(NULL);
    double seconds_now = TUL_seconds();

    double seconds_passed = seconds_now - reference;

    return (time_t) (now - seconds_passed);
}
