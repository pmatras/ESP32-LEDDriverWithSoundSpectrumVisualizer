#include "NetworkConnectivity.h"

void connectToWiFi(const char* WiFi_SSID, const char* WiFi_PASSWD, Adafruit_SSD1306 &display) {
    display.setCursor(0, 0);
    display.println("Connecting to ");
    display.println("");
    display.println(WiFi_SSID);
    display.println("");
    display.print("network...");
    display.display();
    delay(1000);

    WiFi.begin(WiFi_SSID, WiFi_PASSWD);
    while(WiFi.status() != WL_CONNECTED) {
        delay(500);
        display.print(".");
        display.display();
    }

    display.clearDisplay();
    display.setCursor(0,0);
    display.println("Connected to WiFi!");
    display.display();
    delay(1500);

    display.clearDisplay();
    display.setCursor(0,0);
    display.println("IP address: ");
    display.println("");
    display.println("");
    display.println(WiFi.localIP());
    display.display();
    delay(2000);
}