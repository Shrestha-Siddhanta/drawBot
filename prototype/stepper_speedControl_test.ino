
/*
 Stepper Motor Control - speed control

 This program drives a unipolar or bipolar stepper motor.
 The motor is attached to digital pins 8 - 11 of the Arduino.
 A potentiometer is connected to analog input 0.

 The motor will rotate in a clockwise direction. The higher the potentiometer value,
 the faster the motor speed. Because setSpeed() sets the delay between steps,
 you may notice the motor is less responsive to changes in the sensor value at
 low speeds.

 Created 30 Nov. 2009
 Modified 28 Oct 2010
 by Tom Igoe

 */

#include <Stepper.h>

const int stepsPerRevolution = 128;  // change this to fit the number of steps per revolution
// for your motor


// initialize the stepper library on pins :
Stepper myStepper_L(stepsPerRevolution, 12, 10, 9, 11);
Stepper myStepper_R(stepsPerRevolution, 4, 6, 7, 5);
int stepCount = 0;  // number of steps the motor has taken

void setup() {
  // nothing to do inside the setup
}

void loop() {
  // read the sensor value:
  int sensorReading_L = 1000;
  int sensorReading_R = 80;
  // map it to a range from 0 to 100:
  int motorSpeed_L = map(sensorReading_L, 0, 1023, 0, 100);
  int motorSpeed_R = map(sensorReading_R, 0, 1023, 0, 100);
  // set the motor speed:
  if (motorSpeed_L > 0 && motorSpeed_R > 0  ) {
    myStepper_L.setSpeed(motorSpeed_L);
    myStepper_R.setSpeed(motorSpeed_R);
    // step 1/100 of a revolution:
    myStepper_L.step(stepsPerRevolution / 100);
    myStepper_R.step(stepsPerRevolution / 100);
  }
}


