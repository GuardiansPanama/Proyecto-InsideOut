#include <Wire.h>
#include <Servo.h>

// Definición de pines
const int dir1 = 2;
const int vel1 = 3;
const int dir2 = 4;
const int vel2 = 5;
const int ledRojo = 6;
const int pinServo = 7;
const int ledAmarillo = 10;

Servo miServo;
const int I2C_ADDRESS = 0x10;

// Constantes de configuración
const unsigned long TIEMPO_GIRO = 800;
const unsigned long TIEMPO_AVANCE = 1000;
const unsigned long TIEMPO_EVASION = 1000;
const unsigned long TIEMPO_PAUSA = 300;
const int DISTANCIA_MIN = 400;
const int DISTANCIA_MAX = 700;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  
  miServo.attach(pinServo);
  
  // Inicializar servo en 0 grados
  miServo.write(0);
  delay(1000); // Tiempo para llegar a posición inicial
  
  // Configurar pines
  pinMode(ledRojo, OUTPUT);
  pinMode(ledAmarillo, OUTPUT);
  pinMode(dir1, OUTPUT);
  pinMode(vel1, OUTPUT);
  pinMode(dir2, OUTPUT);
  pinMode(vel2, OUTPUT);
  
  Serial.println("=== Sistema de medición angular ===");
  Serial.println("Ángulo | Distancia (mm) | Acción");
  Serial.println("---------------------------------");
}

void loop() {
  // Secuencia de lectura con acciones específicas
  leerYActuar(0, "0°", derecha, TIEMPO_GIRO);
  leerYActuar(90, "90°", adelante, TIEMPO_AVANCE);
  leerYActuar(180, "180°", izquierda, TIEMPO_GIRO);
  
  Serial.println("---------------------------------");
  delay(1000);
}

void leerYActuar(int angulo, const char* nombre, void (*accion)(), unsigned long duracion) {
  // Mover servo al ángulo deseado
  miServo.write(angulo);
  delay(600); // Espera para que el servo se estabilice
  
  // Medir distancia
  int distancia = medirDistancia();
  
  // Mostrar información
  Serial.print(nombre);
  Serial.print("\t| ");
  
  if (distancia == -1) {
    Serial.print("Error\t\t| ");
    indicarError();
    return;
  }
  
  Serial.print(distancia);
  Serial.print(" mm\t| ");
  
  // Tomar decisiones
  if (distancia < DISTANCIA_MIN) {
    Serial.println("Objeto cercano - Evasión");
    protocoloEvasivo();
  }
  else if (distancia <= DISTANCIA_MAX) {
    Serial.println(nombre);
    accion();
    delay(duracion);
    stop();
    delay(TIEMPO_PAUSA);
  }
  else {
    Serial.println("Sin acción - Objeto lejano");
  }
}

// Funciones de movimiento
void adelante() {
  digitalWrite(dir1, LOW);
  digitalWrite(dir2, LOW);
  analogWrite(vel1, 130);
  analogWrite(vel2, 130);
}

void derecha() {
  digitalWrite(dir1, HIGH);
  digitalWrite(dir2, LOW);
  analogWrite(vel1, 130);
  analogWrite(vel2, 130);
}

void izquierda() {
  digitalWrite(dir1, LOW);
  digitalWrite(dir2, HIGH);
  analogWrite(vel1, 130);
  analogWrite(vel2, 130);
}

void stop() {
  analogWrite(vel1, 0);
  analogWrite(vel2, 0);
}

void protocoloEvasivo() {
  digitalWrite(ledRojo, HIGH);
  izquierda();
  delay(TIEMPO_EVASION);
  stop();
  delay(TIEMPO_PAUSA);
  adelante();
  delay(TIEMPO_AVANCE);
  stop();
  digitalWrite(ledRojo, LOW);
}

void indicarError() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(ledAmarillo, HIGH);
    delay(200);
    digitalWrite(ledAmarillo, LOW);
    delay(200);
  }
}

int medirDistancia() {
  Wire.beginTransmission(I2C_ADDRESS);
  Wire.write('D');
  if (Wire.endTransmission() != 0) return -1;
  
  delay(13); // Tiempo necesario para la medición
  
  if (Wire.requestFrom(I2C_ADDRESS, 2) != 2) return -1;
  
  uint16_t distancia = (Wire.read() << 8) | Wire.read();
  
  if (distancia == 2 || distancia == 4 || distancia > 5000) return -1;
  
  return distancia;
}



