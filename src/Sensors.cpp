#include "Sensors.h"

DHT dht(DHTPIN, DHTTYPE);

void initSensors() {
    dht.begin();
    pinMode(PIR_PIN, INPUT);
    pinMode(LDR_PIN, INPUT);
}

float readTemperature() {
    return dht.readTemperature();
}

float readHumidity() {
    return dht.readHumidity();
}

int readAirQuality() {
    return analogRead(MQ135_PIN);
}

bool isMotionDetected() {
    return digitalRead(PIR_PIN) == HIGH;
}

bool isDark() {
    return digitalRead(LDR_PIN) == HIGH;
}
