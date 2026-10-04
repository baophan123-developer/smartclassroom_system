#include <Arduino.h>
#include "Sensors.h"
#include "Outputs.h"
#include "Display.h"

// Ngưỡng nhiệt độ
#define TEMP_THRESHOLD 30.0

// Ngưỡng độ ẩm
#define HUMIDITY_THRESHOLD 75.0

// Ngưỡng chất lượng không khí
#define AIR_QUALITY_THRESHOLD 700


void setup() {

    Serial.begin(115200);

    // Khởi tạo cảm biến
    initSensors();

    // Khởi tạo thiết bị output
    initOutputs();

    // Khởi tạo LCD
    initDisplay();

    Serial.println("Smart Classroom Started!");
}


void loop() {

    // =========================
    // 1. ĐỌC DỮ LIỆU CẢM BIẾN
    // =========================

    float temperature = readTemperature();
    float humidity = readHumidity();
    int airQuality = readAirQuality();

    bool motion = isMotionDetected();
    bool dark = isDark();


    // =========================
    // 2. KIỂM TRA NHIỆT ĐỘ / ĐỘ ẨM
    // =========================

    bool highTemperature = temperature >= TEMP_THRESHOLD;
    bool highHumidity = humidity >= HUMIDITY_THRESHOLD;

    if (highTemperature || highHumidity) {

        setFan(true);

    } else {

        setFan(false);
    }


    // =========================
    // 3. KIỂM TRA CHẤT LƯỢNG KHÔNG KHÍ
    // =========================

    bool dangerousAir = airQuality >= AIR_QUALITY_THRESHOLD;

    if (dangerousAir) {

        // Bật quạt
        setFan(true);

        // Bật Warning LED + Buzzer
        setWarning(true);

    } else {

        // Tắt Warning LED + Buzzer
        setWarning(false);
    }


    // =========================
    // 4. ĐIỀU KHIỂN ĐÈN LỚP
    // =========================

    if (dark && motion) {

        // Trời tối + có người
        setClassLight(true);

    } else {

        // Trời sáng hoặc không có người
        setClassLight(false);
    }


    // =========================
    // 5. CẬP NHẬT LCD
    // =========================

    updateDisplay(
        temperature,
        humidity,
        airQuality,
        dangerousAir
    );



    // =========================
    // 6. HIỂN THỊ SERIAL
    // =========================

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
