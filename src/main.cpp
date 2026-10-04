#include <Arduino.h>

void setup() {
    Serial.begin(115200);
}

void loop() {
    Serial.println("Smart Classroom is running!");
    delay(1000);
}