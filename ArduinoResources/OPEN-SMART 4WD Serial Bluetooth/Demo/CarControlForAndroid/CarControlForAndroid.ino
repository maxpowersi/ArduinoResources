#define BIN1 A3
#define BIN2 A2
#define PWMB 6
#define AIN1 9
#define AIN2 10
#define PWMA 11

void setup()
{
  pinMode(BIN1,OUTPUT);
  pinMode(BIN2,OUTPUT);
  pinMode(PWMB,OUTPUT);
  pinMode(AIN1,OUTPUT);
  pinMode(AIN2,OUTPUT);
  pinMode(PWMA,OUTPUT);

  analogWrite(PWMB,0);  
  analogWrite(PWMA,0);  
}

void loop()
{
  adelante(255);
  delay(1000);
  stop();
  delay(1000);
  
  atras(255);
  delay(1000);
  stop();
  delay(1000);       
  
  adelanteIzq(255);
  delay(1000);
  stop();
  delay(1000);

  adelanteDer(255);
  delay(1000);
  stop();
  delay(1000);
}

void stop()
{
  analogWrite(PWMB,0); 
  analogWrite(PWMA,0); 
}

void adelante(int speed)
{
 adelanteDer(speed);
 adelanteIzq(speed); 
}

void adelanteDer(int speed)
{
  digitalWrite(AIN1,HIGH);
  digitalWrite(AIN2,LOW); 
  analogWrite(PWMA,speed);  
}

void adelanteIzq(int speed)
{
  digitalWrite(BIN1,HIGH);
  digitalWrite(BIN2,LOW); 
  analogWrite(PWMB,speed);  
}

void atras(int speed)
{
  atrasDer(speed);
  atrasIzq(speed);
}

//por alguna razon no me responde el driver de los motres, no puedo hacer q para los 2 mores gire hacia atras.
void atrasIzq(int speed)
{
  digitalWrite(BIN1,LOW);
  digitalWrite(BIN2,HIGH); 
  analogWrite(PWMB,speed);  
}

void atrasDer(int speed)
{
  digitalWrite(AIN1,LOW);
  digitalWrite(AIN2,HIGH); 
  analogWrite(PWMA,speed);  
}
