

#include <Servo.h>

// setup servo
int servoPin = 8;
int PEN_DOWN = 20; // angle of servo when pen is down
int PEN_UP = 110;   // angle of servo when pen is up
Servo penServo;

float wheel_dia=62; //    # mm (increase = spiral out)
float wheel_base=120; //    # mm (increase = spiral in, ccw) 
int steps_rev=128; //        # 512 for 64x gearbox, 128 for 16x gearbox
int delay_time=6; //         # time between steps in ms
//
////letters start at bottom left corner and end at bottom right corner
//float letter_hi=60; // height of letter
//float letter_wi=30; // width of letter

// Stepper sequence org->pink->blue->yel
int L_stepper_pins[] = {12, 10, 9, 11};
int R_stepper_pins[] = {4, 6, 7, 5};

int fwd_mask[][4] =  {{1, 0, 1, 0},
                      {0, 1, 1, 0},
                      {0, 1, 0, 1},
                      {1, 0, 0, 1}};

int rev_mask[][4] =  {{1, 0, 0, 1},
                      {0, 1, 0, 1},
                      {0, 1, 1, 0},
                      {1, 0, 1, 0}};


void setup() {
  randomSeed(analogRead(1)); 
  Serial.begin(9600);
  for(int pin=0; pin<4; pin++){
    pinMode(L_stepper_pins[pin], OUTPUT);
    digitalWrite(L_stepper_pins[pin], LOW);
    pinMode(R_stepper_pins[pin], OUTPUT);
    digitalWrite(R_stepper_pins[pin], LOW);
  }
  penServo.attach(servoPin);
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
    forward(60);  //leftside
    right(90);  
    forward(30);  //top
    right(90);
    forward(30);  //rightside
    right(90);
    forward(32); 
//    penup();
    left(90);
    forward(30);  //rightside
    left(90);
    forward(50);
    
    
    //// print "A"
    left(90);
//    pendown();
    forward(60);  //leftside
    right(90);  
    forward(30);  //top
    right(90);
    forward(30);  //rightside
    right(90);
    forward(35); //A BAR
    backward(35);
    left(90);
    forward(30);  //rightside
    left(90);
    
//    penup();
    forward(20);
//    pendown();

  // print "O"

    forward(30);  //bottom
    backward(30);
    left(90);  
    forward(60);  //rightside
    right(90);
    forward(30); //top
    right(90);
    forward(60); //leftside
    left(90);
//    penup();


    
       
//  penup();
  done();      // releases stepper motor
  while(1);    // wait for reset
}


// ----- HELPER FUNCTIONS -----------
int step(float distance){
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


void forward(float distance){
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


void backward(float distance){
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


void right(float degrees){
  float rotation = degrees / 360.0;
  float distance = wheel_base * 3.1412 * rotation;
  int steps = step(distance);
  for(int step=0; step<steps; step++){
    for(int mask=0; mask<4; mask++){
      for(int pin=0; pin<4; pin++){
        digitalWrite(R_stepper_pins[pin], rev_mask[mask][pin]);
        digitalWrite(L_stepper_pins[pin], rev_mask[mask][pin]);
      }
      delay(delay_time);
    } 
  }   
}


void left(float degrees){
  float rotation = degrees / 360.0;
  float distance = wheel_base * 3.1412 * rotation;
  int steps = step(distance);
  for(int step=0; step<steps; step++){
    for(int mask=0; mask<4; mask++){
      for(int pin=0; pin<4; pin++){
        digitalWrite(R_stepper_pins[pin], fwd_mask[mask][pin]);
        digitalWrite(L_stepper_pins[pin], fwd_mask[mask][pin]);
      }
      delay(delay_time);
    } 
  }   
}


void done(){ // unlock stepper to save battery
  for(int mask=0; mask<4; mask++){
    for(int pin=0; pin<4; pin++){
      digitalWrite(R_stepper_pins[pin], LOW);
      digitalWrite(L_stepper_pins[pin], LOW);
    }
    delay(delay_time);
  }
}


void penup(){
  delay(200);
  Serial.println("PEN_UP()");
  penServo.write(110);
  delay(200);
}


void pendown(){
  delay(200);  
  Serial.println("PEN_DOWN()");
  penServo.write(20);
  delay(200);
}

