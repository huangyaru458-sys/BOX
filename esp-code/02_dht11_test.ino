/*
  ESP32 + DHT11 温湿度验证模块

  接线：
  - DHT11 VCC -> 3.3V 或 5V（按你的模块标识）
  - DHT11 GND -> ESP32 GND
  - DHT11 DATA -> GPIO17
  - 如果你的 DHT11 模块是裸传感器，DATA 需上拉电阻；如果是带板模块，一般已自带上拉

  功能：
  1. 每 2 秒读取一次温湿度。
  2. 串口输出原始状态和解析结果。
  3. 便于验证接线、供电和传感器是否工作正常。
*/

#include <Arduino.h>

static const uint8_t PIN_DHT11 = 17;

struct Dht11Data {
  uint8_t humidityInt;
  uint8_t humidityDec;
  uint8_t tempInt;
  uint8_t tempDec;
  uint8_t checksum;
};

static bool readDht11(Dht11Data &data) {
  uint8_t bits[5] = {0, 0, 0, 0, 0};
  uint8_t byteIndex = 0;
  uint8_t bitIndex = 7;

  pinMode(PIN_DHT11, OUTPUT);
  digitalWrite(PIN_DHT11, HIGH);
  delay(1);
  digitalWrite(PIN_DHT11, LOW);
  delay(20);
  digitalWrite(PIN_DHT11, HIGH);
  delayMicroseconds(30);

  pinMode(PIN_DHT11, INPUT_PULLUP);

  uint32_t t = micros();
  while (digitalRead(PIN_DHT11) == HIGH) {
    if (micros() - t > 100) return false;
  }
  t = micros();
  while (digitalRead(PIN_DHT11) == LOW) {
    if (micros() - t > 100) return false;
  }
  t = micros();
  while (digitalRead(PIN_DHT11) == HIGH) {
    if (micros() - t > 100) return false;
  }

  for (int i = 0; i < 40; i++) {
    t = micros();
    while (digitalRead(PIN_DHT11) == LOW) {
      if (micros() - t > 100) return false;
    }
    uint32_t highStart = micros();
    while (digitalRead(PIN_DHT11) == HIGH) {
      if (micros() - highStart > 120) break;
    }
    uint32_t highDuration = micros() - highStart;
    uint8_t bitValue = (highDuration > 40) ? 1 : 0;

    bits[byteIndex] <<= 1;
    bits[byteIndex] |= bitValue;

    if (bitIndex == 0) {
      bitIndex = 7;
      byteIndex++;
    } else {
      bitIndex--;
    }
  }

  data.humidityInt = bits[0];
  data.humidityDec = bits[1];
  data.tempInt = bits[2];
  data.tempDec = bits[3];
  data.checksum = bits[4];

  uint8_t sum = (uint8_t)(bits[0] + bits[1] + bits[2] + bits[3]);
  return sum == bits[4];
}

void setup() {
  Serial.begin(115200);
  delay(500);
  pinMode(PIN_DHT11, INPUT_PULLUP);

  Serial.println();
  Serial.println(F("ESP32 DHT11 test ready."));
  Serial.println(F("Wiring: DATA -> GPIO17, GND -> GND, VCC -> 3.3V or 5V depending on module."));
}

void loop() {
  Dht11Data data{};
  bool ok = readDht11(data);

  if (ok) {
    float humidity = data.humidityInt + data.humidityDec / 10.0f;
    float temperature = data.tempInt + data.tempDec / 10.0f;

    Serial.print(F("[DHT11] humidity="));
    Serial.print(humidity, 1);
    Serial.print(F("% temperature="));
    Serial.print(temperature, 1);
    Serial.println(F("C"));
  } else {
    Serial.println(F("[DHT11] read failed"));
  }

  delay(2000);
}
