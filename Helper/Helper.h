#ifndef Helper_h
#define Helper_h

#include "Arduino.h"
#include "Servo.h"

class Helper{
    public:
      Helper();
      Servo penServo;
      
      int step(float distance);
      void forward(float distance);
      void backward(float distance);
      void right(float degrees);
      void left(float degrees);
      void done();
      void penup();
      void pendown();
      void arcLeft(int degrees, float wheel_base);
      void arcRight(int degrees, float wheel_base);
};
#endif

