#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include <DHT.h>

#define DHTPIN D3
#define DHTTYPE DHT11

#define MQ135_PIN A0
#define PIR_PIN D1
#define LDR_PIN D2

void initSensors();
float readTemperature();
float readHumidity();
int readAirQuality();
bool isMotionDetected();
bool isDark();

#endif

