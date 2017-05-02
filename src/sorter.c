#pragma config(Sensor, in1,    lineFollower,   sensorLineFollower)
#pragma config(Sensor, dgtl1,  encod,          sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  pushB,          sensorTouch)
#pragma config(Sensor, dgtl11, ind0,           sensorLEDtoVCC)
#pragma config(Sensor, dgtl12, ind1,           sensorLEDtoVCC)
#pragma config(Motor,  port1,           flight,        tmotorVexFlashlight, openLoop, reversed)
#pragma config(Motor,  port2,           mGate,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           mServR,        tmotorServoStandard, openLoop)
#pragma config(Motor,  port4,           mServL,        tmotorServoStandard, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "utilities.c"
#include "indicators.c"
#include "measure.c"
#include "precalibrate.c"

int sp = 45;
int del = 100;

task main() {
  indMode[0] = 2;
  while (!SensorValue[pushB]) doIndicateTick();
  delay(100);
  while (SensorValue[pushB]) doIndicateTick();
  indMode[0] = 4;
  precalibrate();
  indMode[0] = 0;
  indMode[1] = 2;
  while (1) {
  	doIndicateTick();
  }
}