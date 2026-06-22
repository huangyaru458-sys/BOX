/*
  ESP32 + HC-SR501 人体红外验证模块

  接线：
  - HC-SR501 VCC -> 5V
  - HC-SR501 GND -> ESP32 GND
  - HC-SR501 OUT -> GPIO16

  功能：
  1. 检测到人体靠近时串口打印 HIGH。
  2. 没有人体时串口打印 LOW。
  3. 便于验证投放唤醒逻辑。
*/

#include <Arduino.h>

static const uint8_t PIN_PIR = 16;
static int lastState = -1;

void setup() {
  Serial.begin(115200);
  pinMode(PIN_PIR, INPUT);
  Serial.println();
  Serial.println(F("ESP32 HC-SR501 test ready."));
  Serial.println(F("Wiring: OUT -> GPIO16, VCC -> 5V, GND -> GND."));
}

void loop() {
  int state = digitalRead(PIN_PIR);
  if (state != lastState) {
    lastState = state;
    Serial.print(F("[HC-SR501] state="));
    Serial.println(state == HIGH ? F("HIGH (motion)") : F("LOW (idle)"));
  }
  delay(100);
}
