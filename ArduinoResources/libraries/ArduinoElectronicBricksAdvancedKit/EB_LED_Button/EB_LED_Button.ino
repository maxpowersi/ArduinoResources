/*
  EB - LED Button demo code
  
  Detect the state of a LED Button and output the information on Serial Monitor
  
  http://makerstudio.cc
*/
volatile int state = LOW;

void setup()
{
  Serial.begin(9600);
  attachInterrupt(1, pushButton, RISING);//once button been pushed, function pushButton() will be executed
}
void loop()
{
  Serial.println(state);
}
void pushButton()
{
  state = !state;//global veriable changes it's state once button pushed
}
