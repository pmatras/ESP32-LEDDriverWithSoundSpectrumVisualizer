#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const int MICROPHONE_PIN = 33;
const int SCREEN_WIDTH = 128; 
const int SCREEN_HEIGHT = 64;

const int OLED_RESET_PIN = -1;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET_PIN);

void setup() {
   Serial.begin(115200);
   pinMode(MICROPHONE_PIN, INPUT);
   
   if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
      Serial.println(F("SSD1306 allocation failed"));
      return;
   }

   display.display();
   delay(1000);
   display.clearDisplay();
   display.setTextSize(1);
   display.setTextColor(WHITE);
   display.setCursor(0, 0);
   display.println("*Spectrum Visualizer*");
   display.display(); 
}

void loop() {
  
}