#include <FastLED.h>
#include <Wire.h>
#define NUM_LEDS 50
#define LED_PIN 3
#define BRIGHTNESS 125

CRGB leds[NUM_LEDS];
bool runningEffect = false;  // Flag to control if any effect is running
uint8_t currentEffect = 0;  // 0=None, 1=SurpriceFX, 2=YellowFX, 3=RedFx, 4=BlueFx

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);  // Changed to GRB for better color accuracy
  FastLED.setBrightness(BRIGHTNESS);
  delay(1000);
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
  
  Serial.begin(9600);      // USB communication with computer
  Serial2.begin(9600);     // XBee communication
}

void loop() {
  // Check for incoming serial commands
  if (Serial.available() > 0) {
    char recibido = Serial.read();
    
    switch (recibido) {
      case 'A':
        Serial2.write('D');
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
        currentEffect = 1;  // Amarillo
        runningEffect = true;
        break;
      case 'B':
        Serial2.write('E');
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
        currentEffect = 2;  // Azul
        runningEffect = true;
        break;
      case 'C':
        Serial2.write('F');
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
        currentEffect = 3;  // Multicolor
        runningEffect = true;
        break;
      case 'D':
        Serial2.write('G');
        currentEffect = 4;  // BlueFx
        runningEffect = true;
        break;
      case 'X':  // Stop command
        Serial2.write('X');
        runningEffect = false;
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
        break;
      default:
        Serial.println("Comando no reconocido");
    }
  }

  // Run the selected effect if enabled
  if (runningEffect) {
    switch(currentEffect) {
      case 1: YellowFX(); break;
      case 2: BlueFx(); break;
      case 3: SurpriceFX(); break;
      case 4: RedFx(); break;
    }
  }
}

void SurpriceFX() {
  uint8_t color = random8();
  uint8_t num = random8(NUM_LEDS);
  leds[num] = CHSV(color, 255, 255);  // Set random LED to random color
  FastLED.show();
  leds[num] = CRGB::Black;            // Clear the LED
  delay(5);                           // Wait before next LED
}

void YellowFX() {
  // Shift all LEDs down
  for (int i = NUM_LEDS - 1; i > 0; i--) {
    leds[i] = leds[i - 1];
  }
  
  // Add new LED at top with 30% probability
  if (random8(10) < 3) {
    leds[0] = CRGB(255, 255, 0);  // Yellow
  } else {
    leds[0] = CRGB(0, 0, 0);      // Black (off)
  }
  
  FastLED.show();
  delay(100);
}

void RedFx() {
  static bool fadingUp = true;
  static int brightness = 0;
  
  fill_solid(leds, NUM_LEDS, CRGB::Red);
  
  if (fadingUp) {
    brightness += 5;
    if (brightness >= BRIGHTNESS) {
      brightness = BRIGHTNESS;
      fadingUp = false;
    }
  } else {
    brightness -= 5;
    if (brightness <= 0) {
      brightness = 0;
      fadingUp = true;
    }
  }
  
  FastLED.setBrightness(brightness);
  FastLED.show();
  delay(50);
}

void BlueFx ()

{

fill_solid(leds, NUM_LEDS, CHSV(HUE_BLUE, 255, 255));  // Azul saturado
  FastLED.show();
  delay(1000);  // Espera 1 segundo encendido
  
  // Apagar todos los LEDs
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
  delay(1000);  // Espera 1 segundo apagado
}