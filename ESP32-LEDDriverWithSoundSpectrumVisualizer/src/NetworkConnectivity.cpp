#include "NetworkConnectivity.h"
#include <ArduinoJson.h>

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
    delay(500);
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

std::string getClientsRequestAndSendResponse(WiFiClient &client, Adafruit_SSD1306 &display) {
    std::string request = "";

    display.clearDisplay();
    display.setCursor(0,0);

    if(client) {
        display.println("Client connected!");
        display.display();

        while(client.connected()) {
            if(client.available()) {
                char character = client.read();
                request += character;
            } else {
                if(request.find("RGB") != std::string::npos) {
                    client.println("RGB mode chosen!");
                } else {
                    client.println("Music reactive mode chosen!");
                }
            }
        }

        client.stop();
    } else {
        display.println("Cannot obtain");
        display.println("client's connection");
        display.display();
    }
    delay(500);

    return request;
}

std::string parseClientsRequest(std::string &request, RGBColor &color, Adafruit_SSD1306 &display) {
    DynamicJsonDocument parser(90);
    deserializeJson(parser, request.c_str());
    const char* temp = parser["mode"];
    
    std::string mode(temp);
    
    if(mode == "RGB") {
        color.R = parser["R"];
        color.G = parser["G"];
        color.B = parser["B"];
    }

    display.clearDisplay();
    display.setCursor(0,0);
    display.println("mode: ");
    display.println("");
    display.println(mode.c_str());
    display.println("");
    if(mode == "RGB") {
        display.print("R: ");
        display.println(color.R);
        display.print("G: ");
        display.println(color.G);
        display.print("B: ");
        display.println(color.B);
    }
    display.display();
    delay(4000);

    return mode;        
}