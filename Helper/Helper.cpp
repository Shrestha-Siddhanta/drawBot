#include "Arduino.h"
#include "Servo.h"
#include "Helper.h"

 float wheel_dia=62; //    # mm (increase = spiral out)
 float wheel_base=121; //    # mm (increase = spiral in, ccw) 
 int steps_rev=128; //        # 512 for 64x gearbox, 128 for 16x gearbox
 int delay_time=10; //         # time between steps in ms

 int PEN_DOWN = 20; // angle of servo when pen is down
 int PEN_UP = 120;   // angle of servo when pen is up
 Servo penServo;
int L_stepper_pins[] = {12, 10, 9, 11};
 int R_stepper_pins[] = {4, 6, 7, 5};
////letters start at bottom left corner and end at bottom right corner
//float letter_hi=60; // height of letter
//float letter_wi=30; // width of letter

 int fwd_mask[][4] =  {{1, 0, 1, 0}, 
                      {0, 1, 1, 0},
                      {0, 1, 0, 1},
                      {1, 0, 0, 1}};

 int rev_mask[][4] =  {{1, 0, 0, 1},
                      {0, 1, 0, 1},
                      {0, 1, 1, 0},
                      {1, 0, 1, 0}};

Helper::Helper(){
  
}
int Helper::step(float distance){
  int steps = distance * steps_rev / (wheel_dia * 3.1412); //24.61
  /*
  Serial.print(distance);
  Serial.print(" ");
  Serial.print(steps_rev);
  Serial.print(" ");  
  Serial.print(wheel_dia);
  Serial.print(" ");  
  Serial.println(steps);
  delay(1000);*/
  return steps;  
}

void Helper::forward(float distance){
  int steps = step(distance);
  Serial.println(steps);
  for(int step=0; step<steps; step++){
    for(int mask=0; mask<4; mask++){
      for(int pin=0; pin<4; pin++){
        digitalWrite(L_stepper_pins[pin], rev_mask[mask][pin]);
        digitalWrite(R_stepper_pins[pin], fwd_mask[mask][pin]);
      }
      delay(delay_time);
    } 
  }
}

void Helper::backward(float distance){
  int steps = step(distance);
  for(int step=0; step<steps; step++){
    for(int mask=0; mask<4; mask++){
      for(int pin=0; pin<4; pin++){
        digitalWrite(L_stepper_pins[pin], fwd_mask[mask][pin]);
        digitalWrite(R_stepper_pins[pin], rev_mask[mask][pin]);
      }
      delay(delay_time);
    } 
  }
}

void Helper::right(float degrees){
  float rotation = degrees / 360.0;
  float distance = wheel_base * 3.1412 * rotation;
  int steps = step(distance);
  for(int step=0; step<steps; step++){
    for(int mask=0; mask<4; mask++){
      for(int pin=0; pin<4; pin++){
        digitalWrite(R_stepper_pins[pin], rev_mask[mask][pin]);
        digitalWrite(L_stepper_pins[pin], rev_mask[mask][pin]);
      }
      delay(delay_time+5);
    } 
  }   
}

void Helper::left(float degrees){
  float rotation = degrees / 360.0;
  float distance = wheel_base * 3.1412 * rotation;
  int steps = step(distance);
  for(int step=0; step<steps; step++){
    for(int mask=0; mask<4; mask++){
      for(int pin=0; pin<4; pin++){
        digitalWrite(R_stepper_pins[pin], fwd_mask[mask][pin]);
        digitalWrite(L_stepper_pins[pin], fwd_mask[mask][pin]);
      }
      delay(delay_time+5);
    } 
  }   
}

void Helper::done(){ // unlock stepper to save battery
  for(int mask=0; mask<4; mask++){
    for(int pin=0; pin<4; pin++){
      digitalWrite(R_stepper_pins[pin], LOW);
      digitalWrite(L_stepper_pins[pin], LOW);
    }
    delay(delay_time);
  }
}

void Helper::penup(){
  delay(200);
  Serial.println("PEN_UP()");
  penServo.write(110);
  delay(200);
}

void Helper::pendown(){
  delay(200);  
  Serial.println("PEN_DOWN()");
  penServo.write(20);
  delay(200);
}
void Helper::arcLeft(int degrees, float wheel_base) { 
  float rotation = degrees / 360.0;
  float distance = wheel_base * 2 * 3.1412 * rotation;
  int steps = step(distance);
  for(int step=0; step<steps; step++){
    for(int mask=0; mask<4; mask++){
      for(int pin=0; pin<4; pin++){
        digitalWrite(R_stepper_pins[pin], fwd_mask[mask][pin]);
      }
      delay(delay_time);
    } 
  }
}
 
void Helper::arcRight(int degrees, float wheel_base) {
  float rotation = degrees / 360.0;
  float distance = wheel_base * 2 * 3.1412 * rotation;
  int steps = step(distance);
  for(int step=0; step<steps; step++){
    for(int mask=0; mask<4; mask++){
      for(int pin=0; pin<4; pin++){
        digitalWrite(L_stepper_pins[pin], rev_mask[mask][pin]);
      }
      delay(delay_time);
    } 
  }
}
