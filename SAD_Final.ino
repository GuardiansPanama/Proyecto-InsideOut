#include <Wire.h>
#include <Arduino.h>

// Pines para el primer programa (potenciómetro)
const int potPin = A0;
const int dirPin = 11;
const int velPin = 10;
const int LIMITE_ATRAS = 380;
const int LIMITE_ADELANTE = 770;

// Pines para el segundo programa (motores)
int dir1 = 4, vel1 = 5;
int dir2 = 7, vel2 = 6;
int dir3 = 9, vel3 = 8;
int ledPin = 50;

// Variables de control
char mensaje;
bool esperandoComando = true; // Comienza esperando 'E' o 'F'
unsigned long tiempoEspera;

void setup() {
  Serial.begin(9600);
  
  // Configurar pines
  pinMode(dirPin, OUTPUT);
  pinMode(velPin, OUTPUT);
  pinMode(dir1, OUTPUT); pinMode(vel1, OUTPUT);
  pinMode(dir2, OUTPUT); pinMode(vel2, OUTPUT);
  pinMode(dir3, OUTPUT); pinMode(vel3, OUTPUT);
  pinMode(ledPin, OUTPUT);
  
  
}

void loop() {
  // --- Fase 1: Esperar comando serial ('E' o 'F') ---
  if (esperandoComando && Serial.available() > 0) {
    mensaje = Serial.read();
    
    if (mensaje == 'E' || mensaje == 'F') {
      esperandoComando = false; // Salir del modo espera
      
      // Ejecutar segundo programa (E/F)
      if (mensaje == 'E') {
        ejecutarSecuenciaE();
      } else {
        ejecutarSecuenciaF();
      }
      
      // --- Fase 2: Ejecutar primer programa automáticamente ---
      delay(5000); // Espera antes de comenzar
      ejecutarPrimerPrograma();
      
      // --- Volver a esperar comandos (ciclo infinito) ---
      
      esperandoComando = true; // Reiniciar el ciclo
    }
  }
}

// ===== Primer Programa (Potenciómetro - Automático) =====
void ejecutarPrimerPrograma() {
  Serial.println("INICIANDO PRIMER PROGRAMA (AUTOMÁTICO)");
  moverAtras();
  
  enum Estado { MOVIENDO_ATRAS, ESPERANDO, MOVIENDO_ADELANTE };
  Estado estado = MOVIENDO_ATRAS;
  
  while (true) {
    int valorPot = analogRead(potPin);
    

    switch (estado) {
      case MOVIENDO_ATRAS:
        if (valorPot <= LIMITE_ATRAS) {
          detenerMotor();
          tiempoEspera = millis();
          estado = ESPERANDO;
          
        }
        break;
        
      case ESPERANDO:
        if (millis() - tiempoEspera >= 5000) {
          moverAdelante();
          estado = MOVIENDO_ADELANTE;
        }
        break;
        
      case MOVIENDO_ADELANTE:
        if (valorPot >= LIMITE_ADELANTE) {
          detenerMotor();
          
          return; // Salir y volver al loop()
        }
        break;
    }
    delay(50);
  }
}

// ===== Funciones del Segundo Programa (Serial) =====
void ejecutarSecuenciaE() {
  digitalWrite(ledPin, HIGH);
  adelante(); delay(10000); stop(); delay(300);
  derecha(); delay(5000); stop(); delay(1000);
  izquierda(); delay(5000); stop(); delay(300);
  atras(); delay(4000); stop(); delay(300);
  giro(); delay(9000); stop();
  atras(); delay(9000); stop(); delay(500);
  digitalWrite(ledPin, LOW);
}

void ejecutarSecuenciaF() {
  digitalWrite(ledPin, HIGH);
  giroizquierda(); delay(1200); stop(); delay(300);
  giro(); delay(1200); stop(); delay(300);
  adelante(); delay(7000); stop(); delay(500);
  giro(); delay(9000); stop(); delay(500);
  digitalWrite(ledPin, LOW);
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

void moverAtras() {
  digitalWrite(dirPin, LOW);
  analogWrite(velPin, 80);
}

void moverAdelante() {
  digitalWrite(dirPin, HIGH);
  analogWrite(velPin, 235);
}

void detenerMotor() {
  analogWrite(velPin, 0);
}