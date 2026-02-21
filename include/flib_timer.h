#ifndef FLIB_TIMER_H
#define FLIB_TIMER_H

#include "flib_definitions.h"

#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>

    typedef struct flib_time {
        const flib_ui64 start;
        const flib_ui64 frequency;
    } flib_time;

    static inline flib_ui64 flib_get_ticks() {
        flib_ui64 ticks;
        QueryPerformanceCounter((LARGE_INTEGER *)&ticks);
        return ticks;
    }

    static inline flib_ui64 flib_get_frequency() {
        flib_ui64 ticks;
        QueryPerformanceFrequency((LARGE_INTEGER *)&ticks);
        return ticks;
    }

    static inline flib_time flib_timer_create() {
        flib_time timer = {
            .start = flib_get_ticks(),
            .frequency = flib_get_frequency()
        };
        
        return timer;
    }

    static inline flib_ui64 flib_timer_get_ticks(flib_time *timer) {
        return flib_get_ticks() - timer->start;
    }    

    static inline double flib_timer_get_microseconds(flib_time *timer) {
        flib_ui64 elapsed = flib_timer_get_ticks(timer) * 1000000;
        return (double)elapsed / timer->frequency;
    }

    static inline double flib_timer_get_milliseconds(flib_time *timer) {
        return flib_timer_get_microseconds(timer) / 1000;
    }

    static inline double flib_timer_get_seconds(flib_time *timer) {
        return flib_timer_get_milliseconds(timer) / 1000;
    }
#else

#endif
#endif /* FLIB_TIMER_H */