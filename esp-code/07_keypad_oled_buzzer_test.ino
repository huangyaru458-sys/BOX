/*
  ESP32 + 4x4 Keypad + 1.3" OLED + Buzzer test

  Purpose:
  - Show the pressed key on the OLED
  - When key '2' is pressed, the buzzer beeps

  Wiring:
  - OLED SDA -> GPIO21
  - OLED SCL -> GPIO22
  - OLED VCC -> 3.3V
  - OLED GND -> GND
  - Buzzer IO -> GPIO5Buzzer
  -  VCC -> 3.3V or 5V according to your module
  - Buzzer GND -> GND
  - Keypad rows: R1=GPIO18, R2=GPIO19, R3=GPIO23, R4=GPIO32
  - Keypad cols: C1=GPIO25, C2=GPIO26, C3=GPIO13, C4=GPIO33
  - All module grounds must be connected together

  OLED driver:
  - 1.3" OLED is usually SH1106 128x64
  - If your module is SSD1306, change the U8g2 constructor accordingly
*/

#include <Arduino.h>
#include <Wire.h>
#include <Keypad.h>
#include <U8g2lib.h>

static const uint8_t PIN_OLED_SDA = 21;
static const uint8_t PIN_OLED_SCL = 22;
static const uint8_t PIN_BUZZER = 5;

static const uint8_t ROWS = 4;
static const uint8_t COLS = 4;

char keys[ROWS][COLS] = {
  {'1', '4', '7', '*'},
  {'2', '5', '8', '0'},
  {'3', '6', '9', '#'},
  {'A', 'B', 'C', 'D'}
};

// 按你实际接线的左到右顺序：
// 33 13 26 25 / 32 23 19 18
// 先按“上面四个是列、下面四个是行”来映射
byte colPins[COLS] = {33, 13, 26, 25};
byte rowPins[ROWS] = {32, 23, 19, 18};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

char lastKey = '-';
unsigned long lastKeyMs = 0;
unsigned long buzzUntilMs = 0;

void buzzerOn() {
  digitalWrite(PIN_BUZZER, LOW);
}

void buzzerOff() {
  digitalWrite(PIN_BUZZER, HIGH);
}

void beep(uint16_t ms = 180) {
  buzzerOn();
  buzzUntilMs = millis() + ms;
}

void drawScreen() {
  char line1[24];
  char line2[24];
  char line3[24];

  snprintf(line1, sizeof(line1), "KEYPAD TEST");
  snprintf(line2, sizeof(line2), "KEY: %c", lastKey);
  snprintf(line3, sizeof(line3), "2 -> BUZZ");

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x12_tr);
  u8g2.drawStr(0, 16, line1);
  u8g2.drawStr(0, 34, line2);
  u8g2.drawStr(0, 52, line3);
  u8g2.sendBuffer();
}

void setup() {
  Serial.begin(115200);
  delay(200);

  pinMode(PIN_BUZZER, OUTPUT);
  buzzerOff();

  Wire.begin(PIN_OLED_SDA, PIN_OLED_SCL);
  u8g2.setI2CAddress(0x3C << 1);
  u8g2.begin();

  lastKey = '-';
  lastKeyMs = millis();
  drawScreen();

  Serial.println();
  Serial.println(F("Keypad + OLED + buzzer test ready."));
  Serial.println(F("Press 2 to make the buzzer beep."));
}

void loop() {
  char key = keypad.getKey();
  if (key != NO_KEY) {
    lastKey = key;
    lastKeyMs = millis();

    Serial.print(F("[KEY] "));
    Serial.println(key);

    if (key == '2') {
      beep(180);
    }

    drawScreen();
  }

  if (buzzUntilMs != 0 && millis() >= buzzUntilMs) {
    buzzerOff();
    buzzUntilMs = 0;
  }

  if (millis() - lastKeyMs > 3000 && lastKey != '-') {
    lastKey = '-';
    drawScreen();
  }

  delay(10);
}
