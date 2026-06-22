/*
  ESP32 + L298N 风扇验证模块

  接线：
  - L298N ENA -> GPIO27
  - L298N IN1 -> GPIO15
  - L298N IN2 -> GND（固定低电平，不接 ESP32）
  - L298N OUT1 / OUT2 -> 直流风扇两根线
  - L298N 12V/VIN -> 风扇外部电源正极
  - L298N GND -> 风扇外部电源负极
  - L298N GND 必须与 ESP32 GND 共地

  功能：
  1. 上电自动转动 3 秒，停止 3 秒，便于肉眼确认风扇是否正常。
 2. 串口支持 on/off/test/status/help/speed 命令。
 3. ENA 只接一个控制脚，不需要接两个 ESP32 引脚。
*/

#include <Arduino.h>

static const uint8_t PIN_FAN_ENA = 27;
static const uint8_t PIN_FAN_IN1 = 15;
static const uint16_t FAN_PWM_FREQ = 1000;
static const uint8_t FAN_PWM_RES = 8; // 0-255

static bool fanRunning = false;
static uint8_t fanSpeed = 255;

void fanApplySpeed(uint8_t duty) {
  fanSpeed = duty;
  ledcWrite(PIN_FAN_ENA, duty);
  fanRunning = (duty > 0);
}

void fanOn() {
  digitalWrite(PIN_FAN_IN1, HIGH);
  fanApplySpeed(fanSpeed == 0 ? 255 : fanSpeed);
  Serial.println(F("[FAN] ON"));
}

void fanOff() {
  fanApplySpeed(0);
  digitalWrite(PIN_FAN_IN1, LOW);
  Serial.println(F("[FAN] OFF"));
}

void fanTestCycle(uint32_t onMs = 3000, uint32_t offMs = 3000) {
  Serial.println(F("[FAN] test cycle start"));
  fanOn();
  delay(onMs);
  fanOff();
  delay(offMs);
  Serial.println(F("[FAN] test cycle end"));
}

void printHelp() {
  Serial.println();
  Serial.println(F("Commands:"));
  Serial.println(F("  on     -> fan on"));
  Serial.println(F("  off    -> fan off"));
  Serial.println(F("  test   -> run 3s on / 3s off"));
  Serial.println(F("  speed N -> set speed 0-255"));
  Serial.println(F("  status -> print fan state"));
  Serial.println(F("  help   -> show this help"));
  Serial.println();
}

void printStatus() {
  Serial.print(F("[STATUS] fanRunning="));
  Serial.println(fanRunning ? F("true") : F("false"));
  Serial.print(F("[STATUS] fanSpeed="));
  Serial.println(fanSpeed);
}

String readLineFromSerial() {
  static String buffer;
  while (Serial.available() > 0) {
    char c = (char)Serial.read();
    if (c == '\r') continue;
    if (c == '\n') {
      String line = buffer;
      buffer = "";
      line.trim();
      return line;
    }
    buffer += c;
  }
  return "";
}

void setup() {
  Serial.begin(115200);
  delay(300);

  pinMode(PIN_FAN_ENA, OUTPUT);
  pinMode(PIN_FAN_IN1, OUTPUT);
  if (!ledcAttach(PIN_FAN_ENA, FAN_PWM_FREQ, FAN_PWM_RES)) {
    Serial.println(F("[ERR] ledcAttach failed"));
  }

  fanOff();

  Serial.println();
  Serial.println(F("ESP32 L298N fan test ready."));
  printHelp();

  // 上电先做一次验证，方便确认风扇和供电是否正常
  fanTestCycle(3000, 3000);
}

void loop() {
  String cmd = readLineFromSerial();
  if (cmd.length() == 0) {
    delay(10);
    return;
  }

  cmd.toLowerCase();

  if (cmd == "on") {
    fanOn();
  } else if (cmd == "off") {
    fanOff();
  } else if (cmd == "test") {
    fanTestCycle(3000, 3000);
  } else if (cmd == "status") {
    printStatus();
  } else if (cmd == "help") {
    printHelp();
  } else if (cmd.startsWith("speed")) {
    int spacePos = cmd.indexOf(' ');
    if (spacePos > 0) {
      int duty = cmd.substring(spacePos + 1).toInt();
      if (duty < 0) duty = 0;
      if (duty > 255) duty = 255;
      fanApplySpeed((uint8_t)duty);
      digitalWrite(PIN_FAN_IN1, duty > 0 ? HIGH : LOW);
      Serial.print(F("[FAN] speed set to "));
      Serial.println(duty);
    } else {
      Serial.println(F("[ERR] use: speed 0-255"));
    }
  } else {
    Serial.print(F("[ERR] unknown command: "));
    Serial.println(cmd);
    printHelp();
  }
}
