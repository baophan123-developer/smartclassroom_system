#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>

void initDisplay();

void clearDisplay();

void updateDisplay(
    float temperature,
    float humidity,
    int airQuality,
    bool warning
);

#endif
