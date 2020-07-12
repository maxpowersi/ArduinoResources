#include <SoftwareSerial.h>
#include <String.h>
#include <Servo.h> 
#include <car_bluetooth.h>
#include <TM1637Display.h>
#include <MotorDriver.h>
#include <Ultrasonic.h>
#include <math.h>

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

#define LED1 12
#define LED2 13

#define DISPLAY_CLK 4
#define DISPLAY_DIO 2

#define SERVO 3

#define LASER A1

#define BUZZER 5

#define TEMPERATURE A0

#define CMD_INVALID     0XFF

#define CMD_RIGHT_FRONT 'R'
#define CMD_LEFT_FRONT  'L'
#define CMD_FORWARD     'F'
#define CMD_BACKWARD    'B'

#define CMD_STOP_ON        'S'
#define CMD_STOP_OFF        's'

#define CMD_LIGTHS_ON        'W'
#define CMD_LIGTHS_OFF        'w'

#define CMD_SERVO_ON        'V'
#define CMD_SERVO_OFF        'v'

#define CMD_LASER_ON        'U'
#define CMD_LASER_OFF        'u'

#define CMD_TEMPERATURE        'T'

#define CMD_COUNTER        'C'

#define SERVO_STEPS 10

uint8_t currentSpeed = 0;

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

void setup()
{
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  pinMode(LASER, OUTPUT);

  pinMode(BUZZER, OUTPUT);

  servoMotor.attach(SERVO);

  motordriver.init(BIN1,BIN2,PWMB,AIN1,AIN2,PWMA);

  setSpeedForMotors(currentSpeed);

  display.setBrightness(0x0f);

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LASER, LOW);

  bluetooth.waitConnected();
}

void loop()
{
  uint8_t bt_command = bluetooth.readByte();

  if(bt_command != CMD_INVALID)
  {
    //Check velocity
    if((bt_command >= '0') && (bt_command <= '9'))
    {
      currentSpeed = bt_command - 0x30;
      currentSpeed = map(currentSpeed, 0, 9, 0, 255);
      setSpeedForMotors(currentSpeed);
      showSpeed();
    }

    //Check On-Off Commands.
    switch (bt_command)
    {
      case CMD_LIGTHS_ON:
        lightStatus = 1;
        lights();
        break;

      case CMD_LIGTHS_OFF:
        lightStatus = 0;
        lights();
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
        break;
        
      case CMD_STOP_OFF:
        stopEnabled = 0;
        lights();
        break;

      case CMD_TEMPERATURE:
        writeTemperature();
        break;
      
      case CMD_COUNTER:
        counter();
        break;
      
      default:
        break;
    }

    //Check move commands
    if(stopEnabled == 1) 
      motordriver.stop(); 
    else
    {
      switch(bt_command)
      {
        case CMD_FORWARD:
          if(checkDistance())
            break;

          updateNumber();
          motordriver.goForward();
          break;

        case CMD_RIGHT_FRONT:
          updateNumber();
          motordriver.goRight();
          break;

        case CMD_BACKWARD:
          updateNumber();
          motordriver.goBackward();
          break;

        case CMD_LEFT_FRONT:
          updateNumber();
          motordriver.goLeft();
          break;

        default:
          break;
      }
    }
  }

  moveServo();
  stopLights();
}

void lights()
{
  if(stopEnabled == 1) 
          return;

  if(lightStatus == 1)
  {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
  }
  else
  {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
  }
}

long lastStopMove = 0.0;
const long stopInterval = 800;
void stopLights()
{
  if(stopEnabled == 0) 
          return;
  
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);

  unsigned long currentMillis = millis();
  if ( (currentMillis - lastStopMove) <= stopInterval)
     return;
  lastStopMove = currentMillis; 

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
}

void counter()
{
  if(counterDisplay > 10)
    counterDisplay = 0;

    display.showNumberDec(counterDisplay, false);

    counterDisplay++;
}

void showSpeed()
{
   display.showNumberDec(currentSpeed, false);
}

float getTemperature()
{
  int reading = analogRead(TEMPERATURE);
  float voltage = reading * 5.0 / 1024.0; 
  float temperatureC = (voltage - 0.5) * 100 ;
  return voltage;
}

void writeTemperature()
{
  int currentTemp = round(getTemperature());

  uint8_t degrees[] = 
  {
    0x0,
    0x0,
    SEG_A | SEG_B | SEG_F | SEG_G,  // Circle
    SEG_A | SEG_D | SEG_E | SEG_F   // C
  };

  display.setSegments(degrees);
  display.showNumberDec(currentTemp, false, 2, 0);
}

void updateNumber()
{
     if(stepCounterDisplay > 9999)
      stepCounterDisplay = 0;

    display.showNumberDec(stepCounterDisplay, true);

    stepCounterDisplay++;
}

long lastSevoMove = 0.0;
const long servoInterval = 50;
void moveServo()
{
  unsigned long currentMillis = millis();
  if ( (currentMillis - lastSevoMove) <= servoInterval)
     return;
  lastSevoMove = currentMillis; 

  if(servoStatus  == 1)
  {
    //Necesitamos mover el servo
    if(servoPos > servoMax)
        servoDirection = 1;
    
    if(servoPos < servoMin)
        servoDirection = 0;

    if(servoDirection == 0)
      servoPos += SERVO_STEPS;
    else
      servoPos -= SERVO_STEPS;
  }
  else
  {
    //No hay que mover el servo, solamente lo movemos a la pos inicial, si no lo esta
    if(servoPos == servoMax)
      return;

      servoPos = servoMax;
  }

  servoMotor.write(servoPos);
}

void setSpeedForMotors(int8_t speed)
{
  //MOTORA and MOTORB are define in the library.
  motordriver.setSpeed(speed,MOTORA);
  motordriver.setSpeed(speed,MOTORB);
}

int checkDistance()
{
  long microsec = ultrasonic.timing();
  float cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);

  if(cmMsec <= 10)
    ultrasonic_danger_is_near = 1;
  else
    ultrasonic_danger_is_near = 0;

  return ultrasonic_danger_is_near;
}

//Notes
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

//Mario main theme melody
int melody_mario[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7, 
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0, 

  NOTE_C7, 0, 0, NOTE_G6, 
  0, 0, NOTE_E6, 0, 
  0, NOTE_A6, 0, NOTE_B6, 
  0, NOTE_AS6, NOTE_A6, 0, 

  NOTE_G6, NOTE_E7, NOTE_G7, 
  NOTE_A7, 0, NOTE_F7, NOTE_G7, 
  0, NOTE_E7, 0,NOTE_C7, 
  NOTE_D7, NOTE_B6, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6, 
  0, 0, NOTE_E6, 0, 
  0, NOTE_A6, 0, NOTE_B6, 
  0, NOTE_AS6, NOTE_A6, 0, 

  NOTE_G6, NOTE_E7, NOTE_G7, 
  NOTE_A7, 0, NOTE_F7, NOTE_G7, 
  0, NOTE_E7, 0,NOTE_C7, 
  NOTE_D7, NOTE_B6, 0, 0
};
//Mario main them tempo
int melody_time_mario[] = {
  12, 12, 12, 12, 
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12, 

  12, 12, 12, 12,
  12, 12, 12, 12, 
  12, 12, 12, 12, 
  12, 12, 12, 12, 

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
};

void singMario()
{      
     int size = sizeof(melody_mario) / sizeof(int);

     for (int thisNote = 0; thisNote < size; thisNote++) 
     {
       int noteDuration = 1000/melody_time_mario[thisNote];

       buzz(BUZZER, melody_mario[thisNote],noteDuration);

       int pauseBetweenNotes = noteDuration * 1.30;

       delay(pauseBetweenNotes);

       buzz(BUZZER, 0,noteDuration);
    }
}

void buzz(int targetPin, long frequency, long length) 
{
  long delayValue = 1000000/frequency/2; 

  long numCycles = frequency * length/ 1000;

  for (long i=0; i < numCycles; i++)
  { 
    digitalWrite(targetPin,HIGH);
    delayMicroseconds(delayValue);
    digitalWrite(targetPin,LOW);
    delayMicroseconds(delayValue);
  }
}