/*
  Demo code for Project 19 - Stepper Motor Driver  
*/
 
#include <Stepper.h>
 
// Set rotation steps of the stepper motor in a circle
#define STEPS 90
 
// Set connection pins of the stepper motor
Stepper stepper(STEPS, 8, 9, 10, 11);
 
 
 
// set a global variable
int previous = 0;
 
void setup()
{
  // Set speed of the stepper motor as 90 steps per minute
  stepper.setSpeed(90);
}
 
void loop()
{
  // acquire value from a sensor
  int val = analogRead(0);
 
  // Get the moved steps
  stepper.step(val - previous);
 
  // save the last value 
  previous = val;
}