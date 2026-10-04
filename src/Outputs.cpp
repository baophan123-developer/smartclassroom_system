 #include "Outputs.h"

#define FAN_RELAY_PIN D6
#define LIGHT_PIN D5
#define WARNING_LED_PIN D7
#define BUZZER_PIN D0


void initOutputs() {
    pinMode(FAN_RELAY_PIN, OUTPUT);
    pinMode(LIGHT_PIN, OUTPUT);
    pinMode(WARNING_LED_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    setFan(false);
    setClassLight(false);
    setWarning(false);
}

void setFan(bool state) {
    digitalWrite(
        FAN_RELAY_PIN,
        state ? HIGH : LOW
    );
}

void setClassLight(bool state) {
    digitalWrite(
        LIGHT_PIN,
        state ? HIGH : LOW
    );
}

void setWarning(bool state) {
    digitalWrite(
        WARNING_LED_PIN,
        state ? HIGH : LOW
    );

    digitalWrite(
        BUZZER_PIN,
        state ? HIGH : LOW
    );
}
