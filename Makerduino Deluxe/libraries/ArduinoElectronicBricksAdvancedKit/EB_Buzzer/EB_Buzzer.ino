/*
  EB - Buzzer demo code
  
  Make some noise by buzzer
  
  http://makerstudio.cc
*/
const int buzzerPin = 3; 
int volume = 0; // volume of the buzzering

void setup()
{
  pinMode(buzzerPin,OUTPUT); // set as OUTPUT
}

void loop()
{
  //make some Di Di Di Di sound
  for(int i = 0; i < 10; i++){
    digitalWrite(buzzerPin,HIGH);
    delay(200);
    digitalWrite(buzzerPin,LOW);
    delay(200);
  }

  // make noise from low to high 
  for(volume = 0; volume < 255; volume++){
    analogWrite(buzzerPin,volume);
    delay(20);
  }
  
  // make noise from high to low
  for(volume = 255; volume > 0; volume--){
    analogWrite(buzzerPin,volume);
    delay(20);
  }
}
