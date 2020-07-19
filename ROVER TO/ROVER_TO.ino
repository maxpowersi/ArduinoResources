#include <SoftwareSerial.h>
#include <String.h>
#include <Servo.h> 
#include <math.h>
#include <Ultrasonic.h>
#include <car_bluetooth.h>
#include <TM1637Display.h>
#include <PlayRtttl.h>

#define RxD 0
#define TxD 1

#define Trig 7
#define Echo 8

#define BIN1 A3
#define BIN2 A2
#define PWMB 6
#define AIN1 9
#define AIN2 10
#define PWMA 11

#define LED1 13

#define LED_ROJO 12

#define DISPLAY_CLK 4
#define DISPLAY_DIO 2

#define SERVO 3

#define LASER A0

#define BUZZER 5

#define TEMPERATURE A1

#define CMD_INVALID     0XFF

#define CMD_RIGHT_FRONT 'R'
#define CMD_LEFT_FRONT  'L'
#define CMD_FORWARD     'F'
#define CMD_BACKWARD    'B'
#define CMD_STOP    'S'

#define CMD_STOP_ON        'Z'
#define CMD_STOP_OFF        'z'

#define CMD_LIGTHS_ON        'W'
#define CMD_LIGTHS_OFF        'w'

#define CMD_SERVO_ON        'V'
#define CMD_SERVO_OFF        'v'

#define CMD_LASER_ON        'U'
#define CMD_LASER_OFF        'u'

#define CMD_TEMPERATURE        'T'

#define CMD_COUNTER        'C'

#define CMD_BUZZER        'X'

#define CMD_SONG1        'q'
#define CMD_SONG2        'e'
#define CMD_SONG3        'h'
#define CMD_SONG4        'i'
#define CMD_SONG5        'j'
#define CMD_SONG6        'k'
#define CMD_SONG7        'l'
#define CMD_SONG8        'm'
#define CMD_SONG9        'n'
#define CMD_SONG10        'o'
#define CMD_SONG11        'p'
#define CMD_SONG12        'g'

#define CMD_DO        'c'
#define CMD_RE        's'
#define CMD_MI        'x'
#define CMD_FA        't'
#define CMD_SOL        'f'
#define CMD_LA       'b'
#define CMD_SI        'y'

#define SERVO_STEPS 10

uint8_t currentSpeed = 255;

int servoPos = 180;
int servoDirection = 0;
const int servoMax = 180;
const int servoMin = 55;

Servo servoMotor;
CarBluetooth bluetooth(RxD, TxD);
TM1637Display display(DISPLAY_CLK, DISPLAY_DIO);
Ultrasonic ultrasonic(Trig,Echo);

int servoStatus = 0;
int lightStatus = 0;
int laserStatus = 0;
int stepCounterDisplay = 0;
int ultrasonic_danger_is_near = 0;
int stopEnabled = 0;
int counterDisplay = 0;

#define STATUS_MOVE_STOP 0;
#define STATUS_MOVE_FORWARD 1;
#define STATUS_MOVE_BACK 2;
#define STATUS_MOVE_LEFT 3;
#define STATUS_MOVE_RIGHT 4;

int statusMove = STATUS_MOVE_STOP;

void setup()
{
  pinMode(LED1, OUTPUT);
  digitalWrite(LED1, LOW);
  
  pinMode(LASER, OUTPUT);
  digitalWrite(LASER, LOW);

  pinMode(LED_ROJO, OUTPUT);
  digitalWrite(LED_ROJO, LOW);

  pinMode(BUZZER, OUTPUT);
 
  servoMotor.attach(SERVO);

  //Motors setup
  pinMode(BIN1,OUTPUT);
  pinMode(BIN2,OUTPUT);
  pinMode(PWMB,OUTPUT);
  pinMode(AIN1,OUTPUT);
  pinMode(AIN2,OUTPUT);
  pinMode(PWMA,OUTPUT);
  analogWrite(PWMB,0);
  analogWrite(PWMA,0);

  display.setBrightness(0x0f);

  bluetooth.waitConnected();
}

void loop()
{
  checkDistance();
  
  uint8_t bt_command = bluetooth.readByte();
  
  if(bt_command != CMD_INVALID)
  {
    checkSongs(bt_command);
    setVelocity(bt_command);
    checkOnOffCommands(bt_command);
    carDrive(bt_command);
  }

  moveServo();
  stopLights();
}

void setVelocity(uint8_t bt_command)
{
  if((bt_command >= '0') && (bt_command <= '9'))
  {
    currentSpeed = bt_command - 0x30;
    currentSpeed = map(currentSpeed, 0, 9, 0, 255);
    setSpeedForMotors(currentSpeed);
    showSpeed();
  }
}

void checkSongs(uint8_t bt_command)
{
  switch (bt_command)
  {
    case CMD_SONG1:
          playRtttlBlockingPGM(BUZZER, PacMan);
          playRtttlBlockingPGM(BUZZER, Wonderboy);
          break;
    case CMD_SONG2:
          playRtttlBlockingPGM(BUZZER, SMB);
          playRtttlBlockingPGM(BUZZER, SMB_UNDER);
          playRtttlBlockingPGM(BUZZER, SMB_Death);
        break;
    case CMD_SONG3:
          playRtttlBlockingPGM(BUZZER, StarWars);
          playRtttlBlockingPGM(BUZZER, StarwarsI);
      break;
    case CMD_SONG4:
          playRtttlBlockingPGM(BUZZER, Simpsons);
          break;
    case CMD_SONG5:
          playRtttlBlockingPGM(BUZZER, PinkPanther);
          break;
    case CMD_SONG6:
          playRtttlBlockingPGM(BUZZER, AddamsFamily);
          break;
    case CMD_SONG7:
          playRtttlBlockingPGM(BUZZER, TMNT);
          break;
    case CMD_SONG8:
          playRtttlBlockingPGM(BUZZER, Aladin);
          playRtttlBlockingPGM(BUZZER, Hakuna);
          break;
    case CMD_SONG9:
          playRtttlBlockingPGM(BUZZER, Jura);
          break;
    case CMD_SONG10:
          playRtttlBlockingPGM(BUZZER, GhostBuster);
          break;
    case CMD_SONG11:
          playRtttlBlockingPGM(BUZZER, SpongeB);
          break;
    case CMD_SONG12:
          playRtttlBlockingPGM(BUZZER, Batman);
          break;

    case CMD_DO:
          playRtttlBlockingPGM(BUZZER, DO);
          break;
    case CMD_RE:
          playRtttlBlockingPGM(BUZZER, RE);
          break;
    case CMD_MI:
          playRtttlBlockingPGM(BUZZER, MI);
          break;
    case CMD_FA:
          playRtttlBlockingPGM(BUZZER, FA);
          break;
    case CMD_SOL:
          playRtttlBlockingPGM(BUZZER, SOL);
          break;
    case CMD_LA:
          playRtttlBlockingPGM(BUZZER, LA);
          break;
    case CMD_SI:
          playRtttlBlockingPGM(BUZZER, SI);
          break;
    default:
      break;
  }
}

void checkOnOffCommands(uint8_t bt_command)
{
  switch (bt_command)
  {
    case CMD_LIGTHS_ON:
      lightStatus = 1;
      checkLightsStatus();
      break;

    case CMD_LIGTHS_OFF:
      lightStatus = 0;
      checkLightsStatus();
      break;

    case CMD_SERVO_ON:
      servoStatus = 1;
      break;

    case CMD_SERVO_OFF:
      servoStatus = 0;
      break;

    case CMD_LASER_ON:
      laserStatus = 1;
      digitalWrite(LASER, HIGH);
      break;

    case CMD_LASER_OFF:
      laserStatus = 0;
      digitalWrite(LASER, LOW);
      break;

    case CMD_STOP_ON:
      stopEnabled = 1;
      writeStop();
      break;
      
    case CMD_STOP_OFF:
      stopEnabled = 0;
      display.clear();
      checkLightsStatus();
      break;

    case CMD_TEMPERATURE:
      writeTemperature();
      break;
    
    case CMD_COUNTER:
      counter();
      break;
    
    case CMD_BUZZER:
      hacerSonar();
      break;
    
    default:
      break;
  }
}

void carDrive(uint8_t bt_command)
{
  if(stopEnabled == 1) 
    return;

  switch(bt_command)
  {
    case CMD_FORWARD:
      if(ultrasonic_danger_is_near == 1)
        break;
      updateNumber();
      adelante(currentSpeed);
      break;

    case CMD_RIGHT_FRONT:
      updateNumber();
      doblarDerecha(currentSpeed);
      break;

    case CMD_BACKWARD:
      updateNumber();
      atras(currentSpeed);
      break;

    case CMD_LEFT_FRONT:
      updateNumber();
      doblarIzquierda(currentSpeed);
      break;

    case CMD_STOP:
      stop();
      break;

    default:
      break;
  }
}

void checkLightsStatus()
{
  if(stopEnabled == 1) 
          return;

  if(lightStatus == 1)
    digitalWrite(LED1, HIGH);
  else
    digitalWrite(LED1, LOW);
}

void hacerSonar()
{
  analogWrite(BUZZER, 20);
  delay(100);
  analogWrite(BUZZER, 0);

  analogWrite(BUZZER, 20);
  delay(100);
  analogWrite(BUZZER, 0);
}

long lastStopMove = 0.0;
const long stopInterval = 1000;
int ledState = LOW;
void stopLights()
{
  if(stopEnabled == 0) 
    return;
  
 unsigned long currentMillis = millis();

  if (currentMillis - lastStopMove >= stopInterval) 
  {
    lastStopMove = currentMillis;

    if (ledState == LOW) 
      ledState = HIGH;
    else 
      ledState = LOW;

    digitalWrite(LED1, ledState);
  }
}

void counter()
{
  if(counterDisplay > 10)
    counterDisplay = 0;

    display.clear();
    display.showNumberDec(counterDisplay, false);

    counterDisplay++;
}

void showSpeed()
{
  display.clear();
  display.showNumberDec(currentSpeed, false);
}

void writeStop()
{
  uint8_t stop[] = 
  {
    SEG_A | SEG_F | SEG_G | SEG_C | SEG_D ,
    SEG_A | SEG_F | SEG_E,
    SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,
    SEG_E | SEG_A | SEG_B | SEG_F | SEG_G
  };

  display.clear();
  display.setSegments(stop);
}

void writeTemperature()
{
  uint8_t degrees[] = 
  {
    0x0,
    0x0,
    SEG_A | SEG_B | SEG_F | SEG_G,  // Circle
    SEG_A | SEG_D | SEG_E | SEG_F   // C
  };

  //Leemos la entrada  que va de 0 a 1024
  int input = analogRead(TEMPERATURE);

  /*AnalogRead mide sus resultados entre 0 y 1023, para que nos salga un voltaje entre 0 y
  5 voltios vamos a multiplicar el analogRead por 5/1024.*/
  float voltaje = input * 0.004882814;

  //Con esta fórmula, que podeis encontrar en el datasheet que enlazo, transformamos los voltios en grados
  float grados = (voltaje - 0.5) * 100.0;

  //Obtenemos parte entera
  int gradosR = int(grados);

  display.clear();
  display.setSegments(degrees);
  display.showNumberDec(gradosR, false, 2, 0);
}

void updateNumber()
{
     if(stepCounterDisplay > 9999)
      stepCounterDisplay = 0;

    display.clear();
    display.showNumberDec(stepCounterDisplay, true);

    stepCounterDisplay++;
}

long lastSevoMove = 0.0;
const long servoInterval = 50;
void moveServo()
{
  if(servoStatus  == 0)
  {
    if(servoPos != servoMax)
    {
      servoPos = servoMax;
      servoMotor.write(servoPos);
    }

    return;
  }
  
  unsigned long currentMillis = millis();
  if ( (currentMillis - lastSevoMove) <= servoInterval)
     return;
  lastSevoMove = currentMillis; 

  //Necesitamos mover el servo
  if(servoPos > servoMax)
      servoDirection = 1;

  if(servoPos < servoMin)
      servoDirection = 0;

  if(servoDirection == 0)
    servoPos += SERVO_STEPS;
  else
    servoPos -= SERVO_STEPS;

  servoMotor.write(servoPos);
}

void setSpeedForMotors(int8_t speed)
{
  analogWrite(speed,0); 
  analogWrite(speed,0); 
}

int checkDistance()
{
  long microsec = ultrasonic.timing();
  float cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);

  if(cmMsec <= 30)
  {
    ultrasonic_danger_is_near = 1;
    digitalWrite(LED_ROJO, HIGH);
    if(statusMove == 1) stop();
  }
  else
  {
    ultrasonic_danger_is_near = 0;
    digitalWrite(LED_ROJO, LOW);
  }

  return ultrasonic_danger_is_near;
}

void stop()
{
  analogWrite(PWMB,0); 
  analogWrite(PWMA,0); 
  statusMove = STATUS_MOVE_STOP;
}

void adelante(int speed)
{
 statusMove = STATUS_MOVE_FORWARD;
 ladoDerechoAdelante(speed);
 ladoIzquierdoAdelante(speed); 
}

void doblarIzquierda(int speed)
{
  ladoDerechoAdelante(speed);
  statusMove = STATUS_MOVE_LEFT;
}

void doblarDerecha(int speed)
{
  ladoIzquierdoAdelante(speed);
  statusMove = STATUS_MOVE_RIGHT;
}

void atras(int speed)
{
  statusMove = STATUS_MOVE_BACK;
  ladoDerechaAtras(speed);
  ladoIzquierdoAtras(speed);
}

void ladoIzquierdoAtras(int speed)
{
  digitalWrite(BIN1,LOW);
  digitalWrite(BIN2,HIGH); 
  analogWrite(PWMB,speed);  
}

void ladoDerechaAtras(int speed)
{
  digitalWrite(AIN1,LOW);
  digitalWrite(AIN2,HIGH); 
  analogWrite(PWMA,speed);  
}

void ladoDerechoAdelante(int speed)
{
  digitalWrite(AIN1,HIGH);
  digitalWrite(AIN2,LOW); 
  analogWrite(PWMA,speed);  
}

void ladoIzquierdoAdelante(int speed)
{
  digitalWrite(BIN1,HIGH);
  digitalWrite(BIN2,LOW); 
  analogWrite(PWMB,speed);  
}