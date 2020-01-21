#include "LEDDriver.h"

const int LEDS_NUMBER = 60;
CRGB leds[LEDS_NUMBER];
const int DATA_PIN = 12;

CRGB ledsHelper[20];

void setupLEDs() {
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, LEDS_NUMBER);
}

void turnOffLEDs() {
    for(int i = 0; i < LEDS_NUMBER; ++i) {
        leds[i] = CRGB(0, 0, 0);
    }
    FastLED.show();
}

void setRGBColorForLEDs(RGBColor &color) {
    for(int i = 0; i < LEDS_NUMBER; ++i) {
        leds[i] = CRGB(color.R, color.G, color.B);
    }
    FastLED.show();
}

int getLengthOfLEDs(const int &frequency) {
    if(frequency < 9) {
        return 0;
    }
    if(frequency >= 9 && frequency <= 16) {
        return 1;
    }
    if(frequency >= 17 && frequency <= 28) {
        return 2;
    }
    if(frequency >= 29 && frequency <= 40) {
        return 3;
    }
    if(frequency >= 40 && frequency <= 52) {
        return 4;
    }
    if(frequency >= 52 && frequency <= 64) {
        return 5;
    }

    return 0;
}

RGBColor mapFrequencyToColor(const int &frequency) {
    if(frequency >= 9 && frequency <= 12) {
        return RGBColor(115, 5, 240);
    }
    if(frequency >= 13 && frequency <= 16) {
        return RGBColor(240, 24, 5);
    }
    if(frequency >= 17 && frequency <= 22) {
        return RGBColor(240, 140, 5);
    }
    if(frequency >= 23 && frequency <= 28) {
        return RGBColor(240, 240, 5);
    }
    if(frequency >= 29 && frequency <= 34) {
        return RGBColor(115, 240, 5);
    }
    if(frequency >= 35 && frequency <= 40) {
        return RGBColor(5, 115, 20);
    }
    if(frequency >= 41 && frequency <= 46) {
        return RGBColor(5, 150, 200);
    }
    if(frequency >= 47 && frequency <= 52) {
        return RGBColor(0, 10, 140);
    }
    if(frequency >= 53 && frequency <= 58) {
       return RGBColor(130, 5, 200);
    }
    if(frequency >= 59 && frequency <= 64) {
        return RGBColor(255, 0, 210);
    }

    return RGBColor(0, 0, 0);
}

void lightMusicReactive(const int &frequency) {
    int length = getLengthOfLEDs(frequency);

    for(int i = 0; i < 9; ++i) {
        ledsHelper[i] = ledsHelper[i + 1];
    }
    for(int i = 19; i > 10; --i) {
        ledsHelper[i] = ledsHelper[i - 1];    
    }
    
    RGBColor color = mapFrequencyToColor(frequency);
    if(color.R == 0 && color.G == 0 && color.B == 0) {
        for( int i = 0; i < 20; ++i) {
            ledsHelper[i] = CRGB(0, 0, 0);
        }
    }

    for(int i = 0; i < length; ++i) {
        ledsHelper[9 - i] = CRGB(color.R, color.G, color.B);
        ledsHelper[10 + i] = CRGB(color.R, color.G, color.B);
    }

    for(int i = 0; i < 20; ++i) {
        leds[i] = ledsHelper[i];
        leds[i + 20] = ledsHelper[i];
        leds[i + 40] = ledsHelper[i];
    }

    FastLED.show();
}