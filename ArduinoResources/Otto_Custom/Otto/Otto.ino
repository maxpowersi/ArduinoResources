#include <Otto.h>
#include "TM1650.h"
#include "Ultrasonic.h"

#define LeftLeg 2
#define RightLeg 3
#define LeftFoot 4
#define RightFoot 5
#define Buzzer 13

Otto Otto;
TM1650 keyPad(11, 12); // DATA, CLK

int T = 1000;
int moveSize = 15;
int mode = 1;
char key = '-';
bool resetPos = false;

#define echoPin 10 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 9 //attach pin D3 Arduino to pin Trig of HC-SR04
Ultrasonic ultrasonic(trigPin,echoPin);

void receiveSing(int sing)
{
    Otto.home();

    switch (sing)
    {
    case 1:
        Otto.sing(S_connection);
        break;
    case 2:
        Otto.sing(S_disconnection);
        break;
    case 3:
        Otto.sing(S_surprise);
        break;
    case 4:
        Otto.sing(S_OhOoh);
        break;
    case 5:
        Otto.sing(S_OhOoh2);
        break;
    case 6:
        Otto.sing(S_cuddly);
        break;
    case 7:
        Otto.sing(S_sleeping);
        break;
    case 8:
        Otto.sing(S_happy);
        break;
    case 9:
        Otto.sing(S_superHappy);
        break;
    case 10:
        Otto.sing(S_happy_short);
        break;
    case 11:
        Otto.sing(S_sad);
        break;
    case 12:
        Otto.sing(S_confused);
        break;
    case 13:
        Otto.sing(S_fart1);
        break;
    case 14:
        Otto.sing(S_fart2);
        break;
    case 15:
        Otto.sing(S_fart3);
        break;
    case 16:
        Otto.sing(S_mode1);
        break;
    case 17:
        Otto.sing(S_mode2);
        break;
    case 18:
        Otto.sing(S_mode3);
        break;
    case 19:
        Otto.sing(S_buttonPushed);
        break;
    default:
        break;
    }
}

void receiveGesture(int gesture)
{
    Otto.home();

    switch (gesture)
    {
    case 1:
        Otto.playGesture(OttoHappy);
        break;
    case 2:
        Otto.playGesture(OttoSuperHappy);
        break;
    case 3:
        Otto.playGesture(OttoSad);
        break;
    case 4:
        Otto.playGesture(OttoSleeping);
        break;
    case 5:
        Otto.playGesture(OttoFart);
        break;
    case 6:
        Otto.playGesture(OttoConfused);
        break;
    case 7:
        Otto.playGesture(OttoLove);
        break;
    case 8:
        Otto.playGesture(OttoAngry);
        break;
    case 9:
        Otto.playGesture(OttoFretful);
        break;
    case 10:
        Otto.playGesture(OttoMagic);
        break;
    case 11:
        Otto.playGesture(OttoWave);
        break;
    case 12:
        Otto.playGesture(OttoVictory);
        break;
    case 13:
        Otto.playGesture(OttoFail);
        break;
    default:
        break;
    }
}

void move(int moveId)
{
    switch (moveId)
    {
    case 0:
        Otto.home();
        break;
    case 1:
        Otto.walk(1, T, 1);
        break;
    case 2:
        Otto.walk(1, T, -1);
        break;
    case 3:
        Otto.turn(1, T, 1);
        break;
    case 4:
        Otto.turn(1, T, -1);
        break;
    case 5:
        Otto.updown(1, T, moveSize);
        break;
    case 6:
        Otto.moonwalker(1, T, moveSize, 1);
        break;
    case 7:
        Otto.moonwalker(1, T, moveSize, -1);
        break;
    case 8:
        Otto.swing(1, T, moveSize);
        break;
    case 9:
        Otto.crusaito(1, T, moveSize, 1);
        break;
    case 10:
        Otto.crusaito(1, T, moveSize, -1);
        break;
    case 11:
        Otto.jump(1, T);
        break;
    case 12:
        Otto.flapping(1, T, moveSize, 1);
        break;
    case 13:
        Otto.flapping(1, T, moveSize, -1);
        break;
    case 14:
        Otto.tiptoeSwing(1, T, moveSize);
        break;
    case 15:
        Otto.bend(1, T, 1);
        break;
    case 16:
        Otto.bend(1, T, -1);
        break;
    case 17:
        Otto.shakeLeg(1, T, 1);
        break;
    case 18:
        Otto.shakeLeg(1, T, -1);
        break;
    case 19:
        Otto.jitter(1, T, moveSize);
        break;
    case 20:
        Otto.ascendingTurn(1, T, moveSize);
        break;
    default:
        break;
    }
}

void readKeypad()
{
    switch (keyPad.readKey())
    {
    case 0x4c:
        key = '1';
        break;
    case 0x4d:
        key = '4';
        break;
    case 0x4e:
        key = '7';
        break;
    case 0x4f:
        key = '*';
        break;
    case 0x54:
        key = '2';
        break;
    case 0x55:
        key = '5';
        break;
    case 0x56:
        key = '8';
        break;
    case 0x57:
        key = '0';
        break;
    case 0x64:
        key = '3';
        break;
    case 0x65:
        key = '6';
        break;
    case 0x66:
        key = '9';
        break;
    case 0x67:
        key = '#';
        break;
    case 0x74:
        key = 'A';
        break;
    case 0x75:
        key = 'B';
        break;
    case 0x76:
        key = 'C';
        break;
    case 0x77:
        key = 'D';
        break;
    default:
        key = '-';
        break;
    }
}

void modo_movimiento()
{
    int movimiento = 100;
    int cantMoverse = 3;

    switch (key)
    {
        case '1':
            //Waltk
            movimiento = 1;
            break;
        case '2':
             //Walk
            movimiento = 2;
            break;
        case '3':
            //Turn
            movimiento = 3;
            break;
        case '4':
            //Turn
            movimiento = 4;
            break;
        case '5':
            //Jump
            movimiento = 11;
            break;
        case '6':
            //moonwalker
            movimiento = 6;
            break;
        case '7':
            //crusaito
            movimiento = 9;
            break;
        case '8':
            //flapping
            movimiento = 12;
            break;
        case '9':
            //tiptoeSwing
            movimiento = 14;
            break;
        case '0':
            //shakeLeg
            movimiento = 17;
            break;
        case '*':
            //jItter
            movimiento = 19;
            break;
        case '#':
            //Bend
            movimiento = 15;
            break;
        default:
            break;
    }

    if (movimiento == 0)
        return;

    if (movimiento >= 1 && movimiento <=4)
        cantMoverse = 4;
    else
        cantMoverse = 2;

    for (size_t i = 0; i < cantMoverse; i++)
        move(movimiento);
    
    delay(100);

    move(0);
    delay(100);
}

void modo_gesto()
{
    int gesto = 100;

    switch (key)
    {
        case '1':
            gesto = 13;
            break;
        case '2':
            gesto = 2;
            break;
        case '3':
            gesto = 3;
            break;
        case '4':
            gesto = 4;
            break;
        case '5':
            gesto = 5;
            break;
        case '6':
            gesto = 6;
            break;
        case '7':
            gesto = 7;
            break;
        case '8':
            gesto = 8;
            break;
        case '9':
            gesto = 9;
            break;
        case '0':
            gesto = 10;
            break;
        case '*':
            gesto = 11;
            break;
        case '#':
            gesto = 12;
            break;
        default:
            break;
    }

    receiveGesture(gesto);        
    delay(2000);

    move(0);
    delay(1000);
}

void modo_sonido()
{
    int sonido = 100;

    switch (key)
    {
        case '1':
            //S_surprise
            sonido = 3;
            break;
        case '2':
             //S_OhOoh
            sonido = 4;
            break;
        case '3':
            //S_sleeping
            sonido = 7;
            break;
        case '4':
            //S_happy_short
            sonido = 10;
            break;
        case '5':
            //S_sad
            sonido = 11;
            break;
        case '6':
            //S_confused
            sonido = 12;
            break;
        case '7':
            //S_fart1
            sonido = 13;
            break;
        case '8':
            //S_fart2
            sonido = 14;
            break;
        case '9':
            //S_mode1
            sonido = 16;
            break;
        case '0':
            //S_mode2
            sonido = 17;
            break;
        case '*':
            //S_fart3
            sonido = 15;
            break;
        case '#':
            //S_cuddly
            sonido = 6;
            break;
        default:
            break;
    }

    receiveSing(sonido);

    delay(2000);
}

void modo_auto()
{
    if(voy_a_chocar() == false)
    {
     if(resetPos == false)
        {
            Otto.home();
            delay(100);
            resetPos = true;
            receiveSing(5);
            delay(100);
        }

        move(1);
    }
    else
    {
        if(resetPos == true)
        {
            Otto.home();
            delay(100);
            resetPos = false;
            receiveSing(5);
            delay(100);
        }

        move(2);
    }
}

void modeChange()
{
    if (key == 'A')
    {
        if(mode == 1)
            return;

        mode = 1;
        receiveSing(2);
    }

    if (key == 'B')
    {
        if(mode == 2)
            return;

        mode = 2;
        receiveSing(2);
    }

    if (key == 'C')
    {
        if(mode == 3)
            return;

        mode = 3;
        receiveSing(2);
    }

    if (key == 'D')
    {
        if(mode == 4)
            return;

        Otto.home();
        delay(100);
        
        mode = 4;
        receiveSing(2);
    }
}

void setup()
{ 
    Otto.init(LeftLeg, RightLeg, LeftFoot, RightFoot, false, Buzzer);

    delay(1000);
    
    Otto.home();

    delay(1000);

    receiveSing(1);

    delay(1000);
}

int voy_a_chocar()
{
  float cmMsec = ultrasonic.Ranging(CM);

  if(cmMsec <= 10)
    return 1;
  else
    return 0;
}

void loop()
{
    readKeypad();

    if (key != '-')
    {
        modeChange();

        switch (mode)
        {
            case 1:
                modo_movimiento();
                break;
            case 2:
                modo_gesto();
                break;
            case 3:
                modo_sonido();
                break;
            default:
                break;
        }
    }
    else
    {
        //Si no se toco tecla y estamos en modo auto, ejecutamos
        if(mode == 4)
        {
            modo_auto();
        }
    }
}
