#include <SoftwareSerial.h>

#include <Wire.h>
#include <Arduino.h>

int dir1 = 4;                 
int vel1 = 5;                
int dir2 = 7;                 
int vel2 = 6;
int dir3 = 9;                 
int vel3 = 8;
int ledPin = 50;

char mensaje;



void setup()

{
  Serial.begin(9600);
  pinMode(dir1, OUTPUT);
  pinMode(vel1, OUTPUT);
  pinMode(dir2, OUTPUT);
  pinMode(vel2, OUTPUT);
  pinMode(dir3, OUTPUT);
  pinMode(vel3, OUTPUT);
  pinMode (ledPin,OUTPUT);
}

void loop()

{


 if(Serial.available() > 0){ 
 
    mensaje = Serial.read(); 
 

   if(mensaje == 'E'){
digitalWrite (ledPin, HIGH);

adelante () ;

delay (10000);

stop () ;

delay (300);
 
derecha ();

delay (5000);

stop ();

delay (1000);

izquierda ();

delay (5000);

stop ();

delay (300);


atras ();

delay (4000);

stop();

delay (300);

giro();

delay (9000);

stop ();

atras();
 delay (7000);

stop();
delay (500);

digitalWrite (ledPin, LOW);
 
 stop();


    }

 if(mensaje == 'F'){
digitalWrite (ledPin, HIGH);
giroizquierda();
delay (1200),
giro();
delay(1200);
stop();
delay(300);
adelante();
delay(7000);
stop();
delay(500);
giro();
delay (9000);
stop();
digitalWrite (ledPin, LOW);
delay (500);

 }
 }
  

}

void adelante ()
{

digitalWrite(dir1, 1);
  digitalWrite(dir2, 0);
  digitalWrite(dir3, 1);
  analogWrite(vel1, 145);
  analogWrite(vel2, 148);
  analogWrite(vel3, 0);

}


void atras ()
{
digitalWrite(dir1, 0);
     digitalWrite(dir2, 1);
     digitalWrite(dir3, 1);
     analogWrite(vel1, 145);
     analogWrite(vel2, 148);
     analogWrite(vel3, 0);

}


void derecha ()

{
digitalWrite(dir1, 1);
 digitalWrite(dir2, 1);
 digitalWrite(dir3, 0);
 analogWrite(vel1, 85);
 analogWrite(vel2, 85);
 analogWrite(vel3, 171); 

}

void izquierda ()

{

   digitalWrite(dir1, 0);
     digitalWrite(dir2, 0);
     digitalWrite(dir3, 1);
     analogWrite(vel1, 85);
     analogWrite(vel2, 85);
     analogWrite(vel3, 171);
}

void stop ()

{

  analogWrite(vel1, 0);
  analogWrite(vel2, 0);
  analogWrite(vel3, 0);
}

void giro ()


{
digitalWrite(dir1, 1);
     digitalWrite(dir2, 1);
     digitalWrite(dir3, 1);
     analogWrite(vel1, 170);
     analogWrite(vel2, 170);
     analogWrite(vel3, 170);

}

void giroizquierda()

{
digitalWrite(dir2, 0);
     digitalWrite(dir3, 0);
     analogWrite(vel1, 170);
     analogWrite(vel2, 170);
     analogWrite(vel3, 170);
}