#include "NetworkConnectivity.h"

bool connectToWiFi(const char* WiFi_SSID, const char* WiFi_PASSWD, Adafruit_SSD1306 &display) {
    int timeoutCounter = 0;
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
        ++timeoutCounter;
        delay(500);
        display.print(".");
        display.display();

        if(timeoutCounter == 60) {
            display.clearDisplay();
            display.setCursor(0, 0);
            display.println("Failed to connect to");
            display.println("");
            display.println(WiFi_SSID);
            display.display();
            delay(4000);
            return false;
        }
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
    return true;
}

void startServer(WiFiServer &server, const int &port, Adafruit_SSD1306 &display) {
    server.begin();
    display.println("");
    display.println("");
    display.print("Server port: ");
    display.println(port);
    display.display();
}

WiFiClient waitForClientConnection(WiFiServer &server) {
    WiFiClient client;
    do {
        client = server.available();
    } while(!client);

    return client;
}