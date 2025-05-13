void setup() {
  // Inicia la comunicación serial con la computadora (USB)
  Serial.begin(9600);
  
  // Inicia la comunicación serial con el XBee (Serial2 en Arduino Mega)
  Serial2.begin(9600);
  
  
}

void loop() {
  // Verifica si hay datos disponibles desde la computadora
  if (Serial.available() > 0) {
    char recibido = Serial.read(); // Lee el carácter recibido
    
    switch (recibido) {
      case 'A':
        
        Serial2.write('D');
        break;
      case 'B':
        
        Serial2.write('E');
        break;
      case 'C':
        
        Serial2.write('F');
        break;
      default:
        Serial.println("Comando no reconocido");
    }
  }
  
  
}
