/*
  ESP32 + MQ-135 空气质量验证模块

  接线：
  - MQ-135 VCC -> 5V
  - MQ-135 GND -> ESP32 GND
  - MQ-135 AO  -> GPIO34

  功能：
  1. 每 1 秒读取一次 ADC 值。
  2. 串口输出原始模拟量，便于观察变化。
  3. 先验证接线和供电，再做后续阈值判断。
*/

#include <Arduino.h>

static const uint8_t PIN_MQ135 = 34;

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
  analogSetPinAttenuation(PIN_MQ135, ADC_11db);

  Serial.println();
  Serial.println(F("ESP32 MQ-135 test ready."));
  Serial.println(F("Wiring: AO -> GPIO34, VCC -> 5V, GND -> GND."));
}

void loop() {
  int raw = analogRead(PIN_MQ135);
  Serial.print(F("[MQ-135] raw="));
  Serial.println(raw);
  delay(1000);
}
