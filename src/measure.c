#ifndef _measure
#define _measure

struct MaterialMeasurement {
  unsigned int unlitMeasurement;
  unsigned int litMeasurement;
};

struct MaterialMeasurement baseline;
struct MaterialMeasurement materialTypes[4];
int materialsLearned;

struct MaterialMeasurement measurementBuffer;

// helper: get LineFollower Value
int lfv() {
  return SensorValue[lineFollower];
}
// helper: turn flashlight on/off
void light(bool o) {
  motor[flight] = 127 * o;
}

void msrCopy(struct MaterialMeasurement *origin, struct MaterialMeasurement *target) {
  target->unlitMeasurement = origin->unlitMeasurement;
  target->litMeasurement = origin->litMeasurement;
}

void doMeasurement() {
  measurementBuffer.unlitMeasurement = lfv();
  light(1);
  delayInd(100);
  measurementBuffer.litMeasurement = lfv();
  light(0);
}

void takeBaseline() {
  doMeasurement();
  msrCopy(&measurementBuffer, &baseline);
}



#endif
