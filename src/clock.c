#include "ping.h"

size_t getInterval(){
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return tv.tv_usec / 1000;
}

size_t * getRawClock(){
    static size_t clock = 0;

    return &clock;
}

void resetClock(){
    size_t *clock = getRawClock();

    *clock = 0;
}

void startClock(){
    size_t *clock = getRawClock();
    *clock = getInterval();
}

void stopClock(size_t *finalTimer){    
    *finalTimer = getClock();
    resetClock();
}

size_t getClock(){
    size_t clock = *getRawClock();

    if (clock > 0) //is clock is running
        return getInterval() - clock;
    return (0);
}