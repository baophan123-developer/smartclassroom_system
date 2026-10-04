#include <Arduino.h>
#include "Sensors.h"
#include "Outputs.h"
#include "Display.h"

#define TEMP_THRESHOLD 30.0
#define HUMIDITY_THRESHOLD 75.0
#define AIR_QUALITY_THRESHOLD 700

void setup() {

    Serial.begin(115200);
    initSensors();
    initOutputs();
    initDisplay();
    Serial.println("Smart Classroom Started!");
}

void loop() {

    float temperature = readTemperature();
    float humidity = readHumidity();
    int airQuality = readAirQuality();
    bool motion = isMotionDetected();
    bool dark = isDark();

    bool highTemperature = temperature >= TEMP_THRESHOLD;
    bool highHumidity = humidity >= HUMIDITY_THRESHOLD;

    if (highTemperature || highHumidity) {
        setFan(true);
    } else {
        setFan(false);
    }

    bool dangerousAir = airQuality >= AIR_QUALITY_THRESHOLD;

    if (dangerousAir) {
        setFan(true);
        setWarning(true);
    } else {
        setWarning(false);
    }

    if (dark && motion) {
        setClassLight(true);
    } else {
        setClassLight(false);
    }

    updateDisplay(
        temperature,
        humidity,
        airQuality,
        dangerousAir
    );

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" C");

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");

    Serial.print("Air Quality: ");
    Serial.println(airQuality);

    Serial.print("Motion: ");
    Serial.println(motion ? "YES" : "NO");

    Serial.print("Dark: ");
    Serial.println(dark ? "YES" : "NO");

    Serial.println("-------------------------");

    delay(2000);
}
