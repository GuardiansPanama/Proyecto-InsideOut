#include <SoftwareSerial.h>
#include <Servo.h>
#include <Wire.h>
#include <Arduino.h>

int dir1 = 2;                 
int vel1 = 3;                
int dir2 = 4;                 
int vel2 = 5;

int ledPin = 50;
Servo servoder;
Servo servoiz;

char mensaje;


void setup()

{
  Serial.begin(9600);
  pinMode(dir1, OUTPUT);
  pinMode(vel1, OUTPUT);
  pinMode(dir2, OUTPUT);
  pinMode(vel2, OUTPUT);
  pinMode (ledPin,OUTPUT);

  servoder.attach(23);   // Servo 1 en pin 23
  servoiz.attach(25);  // Servo 2 en pin 25

  servoder.write(120);
  servoiz.write(60);
}

void loop()

{


 if(Serial.available() > 0){ 
 
 mensaje = Serial.read(); 
 

   if(mensaje == 'D'){
digitalWrite (ledPin, HIGH);


adelante () ;

delay (4000);

stop () ;

delay (300);

cruzarbrazos();

delay (100);

inicio ();

delay (1000);
brazoarriba();

izquierda ();

delay (1200);

stop ();
delay (300);

derecha ();

delay (1200);

stop ();

delay (300);

derecha ();
delay(1000);

stop ();

delay (300);

izquierda ();

delay (1000);


stop (); 
 delay (300);

 adelante();

 delay (1000);

 stop ();

 delay (300);

 atras ();

 delay (3000);

 inicio();

 stop ();

 delay (300);

 brazoabierto();

 vuelta ();

 delay (9500);

 stop ();

delay (100);

atras ();

delay (1000);

stop();

 
 delay (5000);
 digitalWrite (ledPin, LOW);
 
 stop ();

 

 






  
    }
  
 }
  

}

void atras ()
{

digitalWrite(dir1, 0);
  digitalWrite(dir2, 0);
  analogWrite(vel1, 210);
  analogWrite(vel2, 210);
  

}


void adelante ()
{
digitalWrite(dir1, 1);
     digitalWrite(dir2, 1);
     analogWrite(vel1, 230);
     analogWrite(vel2, 230);
    

}


void izquierda ()

{
digitalWrite(dir1, 0);
 digitalWrite(dir2, 1);
 analogWrite(vel1, 100);
 analogWrite(vel2, 100);
 

}

void derecha ()

{

   digitalWrite(dir1, 1);
     digitalWrite(dir2, 0);
     analogWrite(vel1, 100);
     analogWrite(vel2, 100);
     
}

void stop ()

{

  analogWrite(vel1, 0);
  analogWrite(vel2, 0);
  
}

void vuelta ()

{

 digitalWrite(dir1, 0);
 digitalWrite(dir2, 1);
 analogWrite(vel1, 200);
 analogWrite(vel2, 200); 
  
}

void cruzarbrazos()

{
   for (int pos = 0; pos <= 180; pos += 1) {
    servoder.write(pos);
    servoiz.write(pos);
    delay(5);
  }
  delay(1000);

  for (int pos = 180; pos >= 0; pos -= 1) {
    servoder.write(pos);
    servoiz.write(pos);
    delay(5);
  }
  delay(1000);
}



void brazoabierto()



{
servoder.write(70);
  servoiz.write(110);
  delay (50);

}

void brazoarriba()

{
servoder.write(0);
  servoiz.write(180);
  delay (50);

}

void inicio()

{
servoder.write(120);
servoiz.write(60);

}
