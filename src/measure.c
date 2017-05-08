#ifndef _measure
#define _measure

#include "distance.c"

struct MaterialMeasurement {
  unsigned int unlitMeasurement;
  unsigned int litMeasurement;
};

struct MaterialMeasurement materialTypes[4];
int materialsLearned = 0;

struct MaterialMeasurement measurementBuffer;

// helper: turn flashlight on/off
void light(bool o) {
  motor[flight] = 127 * o;
}

void msrCopy(struct MaterialMeasurement *origin, struct MaterialMeasurement *target) {
  target->unlitMeasurement = origin->unlitMeasurement;
  target->litMeasurement = origin->litMeasurement;
}

void doMeasurement() {
  measurementBuffer.unlitMeasurement = lfv;
  light(1);
  delayInd(100);
  measurementBuffer.litMeasurement = lfv;
  light(0);
}

int getMaterial(bool learn) {
  // distance: variance in lit and unlit values from 
  int dist[4];      // for each material type

  doMeasurement();

  if (learn) {
    // copy this to a new material
    msrCopy(&measurementBuffer, &materialTypes[materialsLearned]);
    // increment the count of materials learned
    materialsLearned++;
    // return the material
    return materialsLearned - 1;
  }

  // otherwise, we're looking for the closest material

  for (int i = 0; i < materialsLearned; ++i) {
    dist[i] = getDistance(measurementBuffer.unlitMeasurement, materialTypes[i].unlitMeasurement,
                          measurementBuffer.litMeasurement, materialTypes[i].litMeasurement);
  }

  // find the index of dist with the smallest value.
  int smallestMaterial = 0;
  int smallestValue = dist[0];
  for (int i = 1; i < 4; ++i) {
    if (dist[i] < smallestValue) {
      smallestValue = dist[i];
      smallestMaterial = i;
    }
  }
  // this is our best possible guess, given what we know.
  return smallestMaterial;
}


#endif
