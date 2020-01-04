#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "../lib/fix_fft/src/fix_fft.h"
#include <WiFi.h>
#include "NetworkConnectivity.h"

const int MICROPHONE_PIN = 33;
const int SCREEN_WIDTH = 128; 
const int SCREEN_HEIGHT = 64;

const int OLED_RESET_PIN = -1;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET_PIN);

const int SAMPLES_COUNT = 128;
int8_t realis[SAMPLES_COUNT];
int8_t imaginalis[SAMPLES_COUNT];
const short y_delimiter = 60;
int sample = 0;

const char* WiFi_SSID = "CHANGE_ME";
const char* WiFi_PASSWD = "CHANGE_ME";

const int SERVER_PORT = 1560;
WiFiServer server(SERVER_PORT);
WiFiClient client;

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

   bool isConnected = connectToWiFi(WiFi_SSID, WiFi_PASSWD, display);
   if(isConnected) {
      startServer(server, SERVER_PORT, display);
      client = waitForClientConnection(server);
   } else {
      display.clearDisplay();
      display.setCursor(0, 0);
      display.println("Cannot start server!");
      display.println("");
      display.println("ESP not connected");
      display.println("to WiFi network");
      display.display();
      delay(4000);
   }
}

void loop() {
   for(int i = 0; i < 128; ++i) {
      sample = analogRead(MICROPHONE_PIN);
      realis[i] = sample / 4 - 128;
      imaginalis[i] = 0;
   }

   fix_fft(realis, imaginalis, 7, 0);

   display.clearDisplay();
   display.setCursor(0, 0);
   display.println("*Spectrum Visualizer*");
  
   for(int i = 1; i < SCREEN_HEIGHT; ++i) {
      int data = sqrt(realis[i] * realis[i] + imaginalis[i] * imaginalis[i]);
            
      display.drawLine(i * 2, y_delimiter, i * 2, y_delimiter - data, WHITE);
   }

   display.display();  
}