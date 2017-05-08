#ifndef _utilities
#define _utilities

#define delayLoop(T, C) clearTimer(3); while(time1[3] < T) C
#define delayInd(T) delayLoop(T, {doIndicateTick();})

int motorPositionFilter() {
  int posm90 = (((SensorValue[encod] % 90) + 90) % 90);
  if (posm90 < 45) {
    return posm90;
  } else {
    return posm90 - 90;
  }
}

struct Configuration {
  int GATE_SPEED;
  int GATE_LENGTH;
  int GATE_TOZERO_DELAY;
  float GATE_TOZERO_SPEED_MULTIPLIER;
  int SERVO_PATH_LEFT;
  int SERVO_PATH_RIGHT;
  int MATERIAL_DISTINCTION_THRESHOLD;
  int SORT_DELAY;
}

struct Configuration CONFIG;

void doConfig() {
  CONFIG.GATE_SPEED = 50;
  CONFIG.GATE_LENGTH = 300;
  CONFIG.GATE_TOZERO_DELAY = 500;
  CONFIG.GATE_TOZERO_SPEED_MULTIPLIER = -2.0;
  CONFIG.SERVO_PATH_LEFT = -90;
  CONFIG.SERVO_PATH_RIGHT = 70;
  CONFIG.MATERIAL_DISTINCTION_THRESHOLD = 40;
  CONFIG.SORT_DELAY = 0;
}

#define mpos SensorValue[encod]
#define mposf motorPositionFilter()
#define lfv SensorValue[lineFollower]
#define mgate motor[rMotorGateId]
#define msr motor[rMotorServRId]
#define msl motor[rMotorServLId]

#endif