#ifndef _measure
#define _measure

struct MaterialMeasurement {
  unsigned int unlitMeasurement;
  unsigned int litMeasurement;
};

struct MaterialMeasurement baseline;
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

void takeBaseline() {
  doMeasurement();
  msrCopy(&measurementBuffer, &baseline);
}

int getMaterial() {
  // distance: sum of squares of differences in lit and unlit
  // int baselinedsq; // for the baseline
  int dsq[4];      // for each material type

  doMeasurement();
  // check closeness to baseline/empty
  // baselinedsq = sqInt(measurementBuffer.unlitMeasurement - baseline.unlitMeasurement) +
  //               sqInt(measurementBuffer.litMeasurement - baseline.litMeasurement);
  // if (baselinedsq < CONFIG.MATERIAL_DISTINCTION_THRESHOLD) {
  //   // no material. return -1 for now and let the caller figure out what to do.
  //   // return -1;
  // }
  for (int i = 0; i < materialsLearned; ++i) {
    dsq[i] = sqInt(measurementBuffer.unlitMeasurement - materialTypes[i].unlitMeasurement) +
             sqInt(measurementBuffer.litMeasurement - materialTypes[i].litMeasurement);
    if (materialsLearned < 4 && dsq[i] < CONFIG.MATERIAL_DISTINCTION_THRESHOLD) {
      // found a material match; return immediately.
      return i;
    }
  }
  // for now, we haven't found a match.
  // if we already have established four materials, just pick the closest
  // otherwise, establish a new one.
  if (materialsLearned == 4) {
    // find the index of dsq with the smallest value.
    int smallestMaterial = 0;
    int smallestValue = dsq[0];
    for (int i = 1; i < 4; ++i) {
      if (dsq[i] < smallestValue) {
        smallestValue = dsq[i];
        smallestMaterial = i;
      }
    }
    // if (200/* * baselinedsq */> smallestValue) {
    //   // this is our best possible guess, given what we know.
      return smallestMaterial;
    // } else {
      // it's closer to the baseline than any learned material, so return that
      // return -1;
    // }
  } else {
    // copy this to a new material
    msrCopy(&measurementBuffer, &materialTypes[materialsLearned]);
    // increment the count of materials learned
    materialsLearned++;
    // return the material
    return materialsLearned - 1;
  }

}


#endif
