#include "LEDDriver.h"

const int LEDS_NUMBER = 60;
CRGB leds[LEDS_NUMBER];
const int DATA_PIN = 12;

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