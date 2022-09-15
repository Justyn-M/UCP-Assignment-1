#define _DEFAULT_SOURCE
#include <time.h>
#include "flicker.h"

void flicker(float sec)
{
    struct timespec ts;
    ts.tv_sec = (int) sec;
    ts.tv_nsec = (sec - ts.tv_sec) * 1000000000;
    nanosleep(&ts, NULL);
}