#include "Display.h"

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <stdio.h>

namespace {

    // LCD I2C
    const uint8_t LCD_ADDRESS = 0x27;
    const uint8_t LCD_COLUMNS = 16;
    const uint8_t LCD_ROWS = 2;

    // Thời gian đổi màn hình
    const unsigned long SCREEN_INTERVAL_MS = 3000;

    // Khởi tạo LCD
    LiquidCrystal_I2C lcd(
        LCD_ADDRESS,
        LCD_COLUMNS,
        LCD_ROWS
    );

    // Biến quản lý màn hình
    unsigned long lastScreenChange = 0;

    bool showingEnvironment = true;
    bool previousWarning = false;
    bool displayReady = false;


    // In một dòng lên LCD
    void printLine(uint8_t row, const char* text) {

        lcd.setCursor(0, row);

        uint8_t column = 0;

        // In nội dung
        while (column < LCD_COLUMNS && text[column] != '\0') {
            lcd.print(text[column]);
            column++;
        }

        // Xóa phần ký tự còn dư
        while (column < LCD_COLUMNS) {
            lcd.print(' ');
            column++;
        }
    }

}


// ==============================
// KHỞI TẠO LCD
// ==============================

void initDisplay() {

    // ESP8266:
    // D2 = SDA
    // D1 = SCL
    Wire.begin(D2, D1);

    lcd.init();
    lcd.backlight();

    // Màn hình khởi động
    printLine(0, "Smart Classroom");
    printLine(1, "System Starting");

    delay(1500);

    lcd.clear();

    // Reset trạng thái
    lastScreenChange = millis();
    showingEnvironment = true;
    previousWarning = false;
    displayReady = true;
}


// ==============================
// XÓA LCD
// ==============================

void clearDisplay() {

    lcd.clear();

    showingEnvironment = true;
    lastScreenChange = millis();
}


// ==============================
// CẬP NHẬT LCD
// ==============================

void updateDisplay(
    float temperature,
    float humidity,
    int airQuality,
    bool dangerousAir
) {

    // Nếu LCD chưa được khởi tạo
    // thì không làm gì
    if (!displayReady) {
        return;
    }


    // ==================================
    // 1. CÓ CẢNH BÁO
    // ==================================

    if (dangerousAir) {

        // Chỉ clear LCD khi vừa bắt đầu cảnh báo
        if (!previousWarning) {
            lcd.clear();
        }

        printLine(0, "!! WARNING !!");
        printLine(1, "AIR DANGER");

        previousWarning = true;

        return;
    }


    // ==================================
    // 2. VỪA HẾT CẢNH BÁO
    // ==================================

    if (previousWarning) {

        lcd.clear();

        previousWarning = false;

        // Quay lại màn hình nhiệt độ
        showingEnvironment = true;

        lastScreenChange = millis();
    }


    // ==================================
    // 3. ĐỔI MÀN HÌNH MỖI 3 GIÂY
    // ==================================

    unsigned long currentTime = millis();

    if (currentTime - lastScreenChange >= SCREEN_INTERVAL_MS) {

        showingEnvironment = !showingEnvironment;

        lastScreenChange = currentTime;
    }


    // ==================================
    // 4. TẠO NỘI DUNG LCD
    // ==================================

    char line1[17];
    char line2[17];


    // Màn hình 1:
    // Temperature + Humidity
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


    // Màn hình 2:
    // Air Quality + Status
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


    // ==================================
    // 5. HIỂN THỊ LÊN LCD
    // ==================================

    printLine(0, line1);
    printLine(1, line2);
}
