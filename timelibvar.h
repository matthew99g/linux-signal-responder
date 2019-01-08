#ifndef __TIME_LIB_VAR
#define __TIME_LIB_VAR

#include "errlib.h"
#include "memlib.h"
#include "getnum.h"

#include <sys/times.h>
#include <time.h>

typedef struct _TIMES_ {
    double realTime;
    double usrTime;
    double sysTime;
} sTimes, *pTimes;

static sTimes
getTimes();

#endif