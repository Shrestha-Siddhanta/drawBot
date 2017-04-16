#include <Helper.h>
#include <Servo.h>

int servoPin = 8;
int cL_stepper_pins[] = {12, 10, 9, 11};
int cR_stepper_pins[] = {4, 6, 7, 5};
Helper helper;

void setup() {
  randomSeed(analogRead(1)); 
  Serial.begin(9600);
  for(int pin=0; pin<4; pin++){
    pinMode(cL_stepper_pins[pin], OUTPUT);
    digitalWrite(cL_stepper_pins[pin], LOW);
    pinMode(cR_stepper_pins[pin], OUTPUT);
    digitalWrite(cR_stepper_pins[pin], LOW);
  }
  helper.penServo.attach(servoPin);
  Serial.println("setup");
  delay(1000);
}

void loop(){ // draw an octagon flower
  helper.pendown();
  for(int x=0; x<10; x++){
    for(int x=0; x<8; x++){
      helper.forward(30);
      helper.left(45);
    }
    helper.left(36);
}
  helper.penup();
  helper.done();      // releases stepper motor
  while(1);    // wait for reset
}
