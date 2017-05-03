#ifndef _gate
#define _gate

void goToZero() {

  delayLoop(CONFIG.GATE_TOZERO_DELAY, {
    mgate = CONFIG.GATE_TOZERO_SPEED_MULTIPLIER * mposf;
    doIndicateTick();
  })

  mgate = 0;
}

#endif
