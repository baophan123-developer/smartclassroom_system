#ifndef OUTPUTS_H
#define OUTPUTS_H

#include <Arduino.h>

void initOutputs();

void setFan(bool state);

void setClassLight(bool state);

void setWarning(bool state);

#endif

