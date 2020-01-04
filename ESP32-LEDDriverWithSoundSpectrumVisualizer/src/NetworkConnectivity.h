#ifndef NetworkConnectivity_H_
#define NetworkConnectivity_H_

#include <WiFi.h>
#include <Adafruit_SSD1306.h>
#include <string>

struct RGBColor {
   int R = 0;
   int G = 0;
   int B = 0;
};

bool connectToWiFi(const char* WiFi_SSID, const char* WiFi_PASSWD, Adafruit_SSD1306 &display);
void startServer(WiFiServer &server, const int &port, Adafruit_SSD1306 &display);
WiFiClient waitForClientConnection(WiFiServer &server);
std::string getClientsRequestAndSendResponse(WiFiClient &client, Adafruit_SSD1306 &display);
std::string parseClientsRequest(std::string &request, RGBColor &color, Adafruit_SSD1306 &display);

#endif