/*************************************************** 
  This is a library for the EB-Motor Driver

  The control signal and the motor use individual power supply.
  
  MakerStudio invests time and resources providing this open source code, 
  please support MakerStudio and open-source hardware by purchasing 
  products from MakerStudio!

  Written by Steve for MakerStudio.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#ifndef _EB_MOTOR_DIRVER_H
#define _EB_MOTOR_DIRVER_H

#include <Arduino.h>


class EB_MotorDriver {
public:
  EB_MotorDriver(uint8_t M1_EN, uint8_t M1_IN2, uint8_t M1_IN1, uint8_t M2_EN, uint8_t M2_IN2, uint8_t M2_IN1);
  void begin();

  void run(int M1_Speed_PWM, int M2_Speed_PWM);
  
  void setM1Speed(int Speed_PWM);
  void setM2Speed(int Speed_PWM);
  
  void stop();
  
private:
  uint8_t M1_EN_pin;
  uint8_t M1_IN1_pin;
  uint8_t M1_IN2_pin;
  
  uint8_t M2_EN_pin;
  uint8_t M2_IN1_pin;
  uint8_t M2_IN2_pin;
  
  
};

#endif
