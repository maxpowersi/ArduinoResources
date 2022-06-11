/*
  Ultrasonic.h - Library for HC-SR04 Ultrasonic Ranging Module.library

  www.23make.taobao.com
*/

#ifndef Ultrasonic_h
#define Ultrasonic_h

#include <Arduino.h>

#define CM 1
#define INC 0

typedef struct{
  int trig;
  int echo;
}ultraPin_t;


class Ultrasonic
{
  public:
    Ultrasonic(int TP, int EP);
    long Timing();
    long Ranging(int sys);

    private:
    int Trig_pin;
    int Echo_pin;
    long  duration,distacne_cm,distance_inc;
    
};

#endif
