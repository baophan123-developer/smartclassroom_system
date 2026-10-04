#include "Display.h"

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <stdio.h>

namespace {

    const uint8_t LCD_ADDRESS = 0x27;
    const uint8_t LCD_COLUMNS = 16;
    const uint8_t LCD_ROWS = 2;
    const unsigned long SCREEN_INTERVAL_MS = 3000;

    LiquidCrystal_I2C lcd(
        LCD_ADDRESS,
        LCD_COLUMNS,
        LCD_ROWS
    );

    unsigned long lastScreenChange = 0;
    bool showingEnvironment = true;
    bool previousWarning = false;
    bool displayReady = false;

    void printLine(uint8_t row, const char* text) {
        lcd.setCursor(0, row);
        uint8_t column = 0;

        while (column < LCD_COLUMNS && text[column] != '\0') {
            lcd.print(text[column]);
            column++;
        }

        while (column < LCD_COLUMNS) {
            lcd.print(' ');
            column++;
        }
    }

}

void initDisplay() {

    Wire.begin(D2, D1);
    lcd.init();
    lcd.backlight();

    printLine(0, "Smart Classroom");
    printLine(1, "System Starting");
    delay(1500);
    lcd.clear();

    lastScreenChange = millis();
    showingEnvironment = true;
    previousWarning = false;
    displayReady = true;
}

void clearDisplay() {
    lcd.clear();
    showingEnvironment = true;
    lastScreenChange = millis();
}

void updateDisplay(
    float temperature,
    float humidity,
    int airQuality,
    bool dangerousAir
) {

    if (!displayReady) {
        return;
    }

    if (dangerousAir) {
        if (!previousWarning) {
            lcd.clear();
        }

        printLine(0, "!! WARNING !!");
        printLine(1, "AIR DANGER");
        previousWarning = true;
        return;
    }

    if (previousWarning) {
        lcd.clear();
        previousWarning = false;
        showingEnvironment = true;
        lastScreenChange = millis();
    }

    unsigned long currentTime = millis();
    if (currentTime - lastScreenChange >= SCREEN_INTERVAL_MS) {
        showingEnvironment = !showingEnvironment;
        lastScreenChange = currentTime;
    }

    char line1[17];
    char line2[17];

    if (showingEnvironment) {
        snprintf(
            line1,
            sizeof(line1),
            "Temp: %.1f C",
            temperature
        );

        snprintf(
            line2,
            sizeof(line2),
            "Hum : %.1f %%",
            humidity
        );
    }

    else {
        snprintf(
            line1,
            sizeof(line1),
            "Air : %d",
            airQuality
        );

        snprintf(
            line2,
            sizeof(line2),
            "Status: OK"
        );
    }

    printLine(0, line1);
    printLine(1, line2);
}
