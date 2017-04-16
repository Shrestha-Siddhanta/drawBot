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
//  pendown();
  // five petal flower
//  for(int m=0; m<1; m++){
      for(int x=0; x<5; x++){
        for(int i=0; i<2; i++){
          helper.arcLeft(160, 30);
        }
         helper.left(98);
        for(int j=0; j<2; j++){
            helper.arcLeft(160, 30); 
          }
         helper.left(36);
  }  
  helper.done();      // releases stepper motor
//  while(1);    // wait for reset
}


