#ifndef LEDDriver_H_
#define LEDDriver_H_

#include "NetworkConnectivity.h"
#include <FastLED.h>

void setupLEDs();
void turnOffLEDs();
void setRGBColorForLEDs(RGBColor &color);
void lightMusicReactive(const int &frequency);

#endif