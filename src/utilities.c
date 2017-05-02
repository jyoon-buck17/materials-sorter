#ifndef _utilities
#define _utilities

#define delayLoop(T, C) clearTimer(3); while(time1[3] < T) C
#define delayInd(T) delayLoop(T, {doIndicateTick();})

#endif