// 

#include <Servo.h>
#include <Stepper.h>

// setup servo
int servoPin = 8;
int PEN_DOWN = 0; // angle of servo when pen is down
int PEN_UP = 180;   // angle of servo when pen is up
Servo penServo;

float wheel_dia=63; //    # mm (increase = spiral out)
float wheel_base=122; //    # mm (increase = spiral in, ccw) 
int steps_rev=128; //        # 512 for 64x gearbox, 128 for 16x gearbox
int delay_time=5; //         # time between steps in ms

float letter_hi=60; // height of letter
float letter_wi=30; // width of letter

// Stepper sequence org->pink->blue->yel
int R_stepper_pins[]= {12, 10, 9, 11};
int L_stepper_pins[] = {4, 6, 7, 5};

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
  Serial.println("setup"
  
  penup();
  
  delay(500);
}


void loop(){ // draw a calibration box 4 times
// print "A"
  for(int y=0;y<4;y++){
    left(90);
    forward(letter_hi);  //leftside
    right(90);  
    forward(letter_wi);  //top
    right(90);
    forward(.5*letter_hi);  //rightside
    right(90);
    forward(letter_wi); //A BAR
    backward(letter_wi);
    left(90);
    forward(.5*letter_hi);  //rightside
    left(90);
  } 
  
/// print "B"
//  for(int y=0;y<4;y++){
//    forward(letter_wi);
//    backward(letter_wi);
//    left(90);
//    forward(letter_hi);
//    right(90);
//    forward(.75*letter_wi);
//    right(90);
//    forward(.5*letter_hi);
//    right(90);
//    forward(.75*letter_wi);
//    backward(letter_wi);
//    left(90);
//    forward(.5*letter_hi);
//    left(90);
//  }
  
  // print "O"
  for(int y=0;y<4;y++){
    forward(letter_wi);  //bottom
    backward(letter_wi);
    left(90);  
    forward(letter_hi);  //rightside
    right(90);
    forward(letter_wi); //top
    right(90);
    forward(letter_hi); //leftside
    left(90);
  }
  
  // print "P"
  for(int y=0;y<4;y++){
    left(90);
    forward(letter_hi);  //leftside
    right(90);  
    forward(letter_wi);  //top
    right(90);
    forward(.5*letter_hi);  //rightside
    right(90);
    forward(letter_wi); //P BAR
    //letter is complete, need to lift pen and move to 'end point'
    //penup
    //backward(letter_wi);
    //left(90);
    //forward(.5*letter_hi);  //rightside
    //left(90);
  } 
  
//    circle( 200, 1000);

//  penup();
  done();      // releases stepper motor
  while(1);    // wait for reset
}


// ----- HELPER FUNCTIONS -----------
int step(float distance){
  int steps = distance * steps_rev / (wheel_dia * 3.1412); //24.61
  
  Serial.print(distance);
  Serial.print(" ");
  Serial.print(steps_rev);
  Serial.print(" ");  
  Serial.print(wheel_dia);
  Serial.print(" ");  
  Serial.println(steps);
  delay(1000);
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
  delay(250);
  Serial.println("PEN_UP()");
  penServo.write(PEN_UP);
  delay(250);
}


void pendown(){
  delay(250);  
  Serial.println("PEN_DOWN()");
  penServo.write(PEN_DOWN);
  delay(250);
}

void circle(int l,  int r
 ){
  // initialize the stepper library on pins :
  Stepper myStepper_L(steps_rev, 12, 10, 9, 11);
  Stepper myStepper_R(steps_rev, 4, 6, 7, 5);
  int stepCount = 0;  // number of steps the motor has taken
    // read the sensor value:
  int sensorReading_L = l;
  int sensorReading_R = r;
  // map it to a range from 0 to 100:
  int motorSpeed_L = map(sensorReading_L, 0, 1023, 0, 100);
  int motorSpeed_R = map(sensorReading_R, 0, 1023, 0, 100);
  // set the motor speed:
  if (motorSpeed_L > 0 && motorSpeed_R > 0  ) {
    myStepper_L.setSpeed(motorSpeed_L);
    myStepper_R.setSpeed(motorSpeed_R);
    // step 1/100 of a revolution:
    myStepper_L.step(steps_rev / 100);
    myStepper_R.step(steps_rev / 100);
  }
  }
