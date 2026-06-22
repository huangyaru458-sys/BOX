/*
  ESP32 + MPU6050 姿态验证模块

  接线：
  - MPU6050 VCC -> 3.3V
  - MPU6050 GND -> ESP32 GND
  - MPU6050 SDA -> GPIO21
  - MPU6050 SCL -> GPIO22

  功能：
  1. 通过 I2C 读取原始加速度和陀螺仪数据。
  2. 串口打印原始值，便于确认模块在线和姿态变化。
*/

#include <Arduino.h>
#include <Wire.h>

static const uint8_t MPU_ADDR = 0x68;

int16_t ax, ay, az, gx, gy, gz;

void mpuWrite(uint8_t reg, uint8_t val) {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(reg);
  Wire.write(val);
  Wire.endTransmission(true);
}

bool mpuReadRaw() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  if (Wire.endTransmission(false) != 0) return false;

  if (Wire.requestFrom(MPU_ADDR, (uint8_t)14, (uint8_t)true) != 14) return false;

  ax = (Wire.read() << 8) | Wire.read();
  ay = (Wire.read() << 8) | Wire.read();
  az = (Wire.read() << 8) | Wire.read();
  Wire.read(); Wire.read(); // temperature, ignore
  gx = (Wire.read() << 8) | Wire.read();
  gy = (Wire.read() << 8) | Wire.read();
  gz = (Wire.read() << 8) | Wire.read();
  return true;
}

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);

  mpuWrite(0x6B, 0x00); // wake up MPU6050

  Serial.println();
  Serial.println(F("ESP32 MPU6050 test ready."));
  Serial.println(F("Wiring: SDA -> GPIO21, SCL -> GPIO22, VCC -> 3.3V, GND -> GND."));
}

void loop() {
  if (mpuReadRaw()) {
    Serial.print(F("[MPU6050] A("));
    Serial.print(ax);
    Serial.print(F(", "));
    Serial.print(ay);
    Serial.print(F(", "));
    Serial.print(az);
    Serial.print(F(") G("));
    Serial.print(gx);
    Serial.print(F(", "));
    Serial.print(gy);
    Serial.print(F(", "));
    Serial.print(gz);
    Serial.println(F(")"));
  } else {
    Serial.println(F("[MPU6050] read failed"));
  }
  delay(1000);
}
