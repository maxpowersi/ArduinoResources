//Demo code for Project 18 - DC Motor 
//you can change the mode by adjust the position of /*...*/
//in the sketch like this  
//  /*motorOnThenOff();
//  motorOnThenOffWithSpeed();*/
//  motorAcceleration();
//reload the sketch, then motorAcceleration() be activated

int motorPin = 9; //pin the motor is connected to

void setup() 
{
  pinMode(motorPin, OUTPUT);
}

void loop() // run over and over again
{
  motorOnThenOff();
  /*motorOnThenOffWithSpeed();
  motorAcceleration();*/
}

void motorOnThenOff(){
  int onTime = 2500; //on time
  int offTime = 1000; //off time
  digitalWrite(motorPin, HIGH);// turns the motor On
  delay(onTime); // waits for onTime milliseconds
  digitalWrite(motorPin, LOW);//turns the motor Off
  delay(offTime);// waits for offTime milliseconds
}
void motorOnThenOffWithSpeed(){
  int onSpeed = 200;// a number between 0 (stopped) and 255 (full speed)
  int onTime = 2500;
  int offSpeed = 50;// a number between 0 (stopped) and 255 (full speed)
  int offTime = 1000;
  analogWrite(motorPin, onSpeed);// turns the motor On
  delay(onTime); // waits for onTime milliseconds
  analogWrite(motorPin, offSpeed);// turns the motor Off
  delay(offTime); // waits for offTime milliseconds
}
void motorAcceleration(){
  int delayTime = 50; //time between each speed step
  for(int i = 0; i < 256; i++){//goes through each speed from 0（127）to 255
    analogWrite(motorPin, i); //sets the new speed
    delay(delayTime);// waits for delayTime milliseconds
  }
  for(int i = 255; i >= 0; i--){//goes through each speed from 255 to 0（127）
    analogWrite(motorPin, i); //sets the new speed
    delay(delayTime);//waits for delayTime milliseconds
  }
}

    