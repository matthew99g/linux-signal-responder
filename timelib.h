#include "timelibvar.h"

static sTimes
getTimes()
{
    struct tms t;
    sTimes stime = { 0 };
    clock_t clockTime = 0;
    static long clockTicks = 0;

    memset(&stime, 0, sizeof(sTimes));

    if (clockTicks == 0) {
        clockTicks = sysconf(_SC_CLK_TCK);
        if(clockTicks == -1)
            errnoExit("sysconf");
    }

    clockTime = clock();
    if(clockTime == -1)
        errnoExit("clock");

    if(times(&t) == -1)
        errnoExit("times");

    stime.sysTime = (double) t.tms_stime / clockTicks;
    stime.usrTime = (double) t.tms_utime / clockTicks;
    stime.realTime = ((double) t.tms_utime / clockTicks) +
                     ((double) t.tms_stime / clockTicks);

    return stime;
}