#include <Helper.h>
#include <Servo.h>

Helper helper;
 int servoPin = 8;
int cL_stepper_pins[] = {12, 10, 9, 11};
 int cR_stepper_pins[] = {4, 6, 7, 5};
 
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
//  penup();
  delay(1000);
}

void loop(){ // draw a calibration box 4 times
//   pendown();
//    for(int y = 0; y<8; y++){
//      forward(30);
//      right(90);
//    }
////    penup();
//    right(90);
//    forward(60);
//    left(90);
//
//   
   // Print P
   //pendown();
    helper.forward(60);  //leftside
    helper.right(90);  
    helper.forward(30);  //top
    helper.right(90);
    helper.forward(30);  //rightside
    helper.right(90);
    helper.forward(32); 
//    penup();
    helper.left(90);
    helper.forward(30);  //rightside
    helper.left(90);
    helper.forward(50);
    
    
    //// print "A"
    helper.left(90);
//    pendown();
    helper.forward(60);  //leftside
    helper.right(90);  
    helper.forward(30);  //top
    helper.right(90);
    helper.forward(30);  //rightside
    helper.right(90);
    helper.forward(35); //A BAR
    helper.backward(35);
    helper.left(90);
    helper.forward(30);  //rightside
    helper.left(90);
    
//    penup();
    helper.forward(20);
//    pendown();

  // print "O"
    helper.forward(30);  //bottom
    helper.backward(30);
    helper.left(90);  
    helper.forward(60);  //rightside
    helper.right(90);
    helper.forward(30); //top
    helper.right(90);
    helper.forward(60); //leftside
    helper.left(90);
//    penup();
//  penup();
    helper.done();      // releases stepper motor
    while(1);    // wait for reset
}


