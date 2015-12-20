// Shipeng Xu
// billhsu.x@gmail.com

#include "Utility.h"

unsigned long getMicroSec() {
    struct timespec ts;
#ifdef __APPLE__  // OS X does not have clock_gettime, use clock_get_time
    clock_serv_t cclock;
    mach_timespec_t mts;
    host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
    clock_get_time(cclock, &mts);
    mach_port_deallocate(mach_task_self(), cclock);
    ts.tv_sec = mts.tv_sec;
    ts.tv_nsec = mts.tv_nsec;
#else
    clock_gettime(CLOCK_REALTIME, &ts);
#endif

    return 1000000 * ts.tv_sec + ts.tv_nsec / 1000;
}

unsigned long getMilliSec() {
    struct timespec ts;
#ifdef __MACH__  // OS X does not have clock_gettime, use clock_get_time
    clock_serv_t cclock;
    mach_timespec_t mts;
    host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
    clock_get_time(cclock, &mts);
    mach_port_deallocate(mach_task_self(), cclock);
    ts.tv_sec = mts.tv_sec;
    ts.tv_nsec = mts.tv_nsec;
#else
    clock_gettime(CLOCK_REALTIME, &ts);
#endif
    return 1000 * ts.tv_sec + ts.tv_nsec / 1000000;
}

bool floatEq(float a, float b) {
    return fabs(a - b) < 0.000001f;
}

float deg2rad(float deg) {
    return deg * PI / 180;
}

float rad2deg(float rad) {
    return rad * 180 / PI;
}

float mapValueWithRange(float value, float inputMin, float inputMax,
                        float outputMin, float outputMax, bool clamp) {
    float ratio = (inputMin - value) / (inputMax - inputMin);
    float newValue = outputMin + (outputMax - outputMin) * ratio;
    if (clamp) {
        if (newValue > outputMax) {
            newValue = outputMax;
        } else if (newValue < outputMin) {
            newValue = outputMin;
        }
    }
    return newValue;
}
