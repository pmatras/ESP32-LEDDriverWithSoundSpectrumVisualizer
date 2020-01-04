#ifndef NetworkConnectivity_H_
#define NetworkConnectivity_H_

#include <WiFi.h>
#include <Adafruit_SSD1306.h>

void connectToWiFi(const char* WiFi_SSID, const char* WiFi_PASSWD, Adafruit_SSD1306 &display);

#endif