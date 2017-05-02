#ifndef _precalibrate
#define _precalibrate

void precalibrate() {
  SensorValue[encod] = 0;

  motor[mGate] = 0;

  takeBaseline();
}

#endif
