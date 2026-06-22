/*
  ESP32 + HC-SR04 超声波验证模块

  接线：
  - HC-SR04 VCC -> 5V
  - HC-SR04 GND -> ESP32 GND
  - HC-SR04 Trig -> GPIO2
  - HC-SR04 Echo -> GPIO4
  - 如果你的模块 Echo 输出是 5V，建议加分压再进 ESP32

  功能：
  1. 每 1 秒测一次距离。
  2. 串口直接输出厘米值。
*/

#include <Arduino.h>

static const uint8_t PIN_TRIG = 2;
static const uint8_t PIN_ECHO = 4;

float readDistanceCm() {
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  unsigned long duration = pulseIn(PIN_ECHO, HIGH, 30000UL);
  if (duration == 0) return -1.0f;

  return duration * 0.0343f / 2.0f;
}

void setup() {
  Serial.begin(115200);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  digitalWrite(PIN_TRIG, LOW);

  Serial.println();
  Serial.println(F("ESP32 HC-SR04 test ready."));
  Serial.println(F("Wiring: Trig -> GPIO2, Echo -> GPIO4, VCC -> 5V, GND -> GND."));
}

void loop() {
  float cm = readDistanceCm();
  if (cm < 0) {
    Serial.println(F("[HC-SR04] read timeout"));
  } else {
    Serial.print(F("[HC-SR04] distance="));
    Serial.print(cm, 1);
    Serial.println(F(" cm"));
  }
  delay(1000);
}
