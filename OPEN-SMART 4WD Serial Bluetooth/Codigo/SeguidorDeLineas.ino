//------------------------------------------------------------
//Funcion: Detecta si una linea es blanca o negra   
//Parametro:   Cuando la señal digital es ALTA, la linea es negra
//             Cuando la señal digital es BAJA, la linea es blanca
//-------------------------------------------------------------
int signalPin =  12;    // connected to digital pin 3
void setup()   {                
  pinMode(signalPin, INPUT); // initialize the digital pin as an output:  
  Serial.begin(9600);  // initialize serial communications at 9600 bps:
}
// the loop() method runs over and over again,
// as long as the Arduino has power
void loop()                     
{
  if(HIGH == digitalRead(signalPin))
    Serial.println("Negro");
    else  Serial.println("Blanco");  // display the color
}
 
