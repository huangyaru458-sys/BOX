#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <EEPROM.h>
#include <Keypad.h>
#include <WebServer.h>
#include <U8g2lib.h> 
#define WIFI_SSID "hhhhhh"
#define WIFI_PASS "huangyaru"
#define MQTT_SERVER "192.168.222.228"
#define MQTT_PORT 1883
#define MQTT_USER ""
#define MQTT_PASS "" 
#define AP_SSID "CLOTHES_BOX_AP"
#define AP_PASS "12345678"
#define AP_IP "192.168.4.1" 
#define DEVICE_ID "ESP32_BOX_001"
#define ADMIN_PASSWORD "123456" 
#define PIN_DHT11 17
#define PIN_MQ135 34
#define PIN_TRIG 2
#define PIN_ECHO 35
#define PIN_PIR 16
#define PIN_MPU_SDA 21
#define PIN_MPU_SCL 22
#define PIN_OLED_SDA 21
#define PIN_OLED_SCL 22
#define PIN_BUZZER 5
#define PIN_LED_NORMAL 14
#define PIN_LED_ALERT 14
#define PIN_FRONT_DOOR_LIGHT 33
#define PIN_BACK_DOOR_LIGHT 12
#define PIN_FAN_ENA 27
#define PIN_FAN_IN1 15
#define PIN_KEY_R1 18
#define PIN_KEY_R2 19
#define PIN_KEY_R3 23
#define PIN_KEY_R4 32
#define PIN_KEY_C1 25
#define PIN_KEY_C2 26
#define PIN_KEY_C3 13
#define PIN_KEY_C4 4
#define FAN_PWM_FREQ 1000
#define FAN_PWM_RES 8 
#define MPU_ADDR 0x68
#define OLED_ADDR 0x3C 
#define MAX_PASSWORD_LEN 6
#define PASSWORD_TIMEOUT 5000
#define BUZZER_BEEP_MS 180 
#define SENSOR_UPDATE_INTERVAL 2000
#define MQTT_PUBLISH_INTERVAL 2000
#define OLED_UPDATE_INTERVAL 1000
#define WIFI_RECONNECT_INTERVAL 5000
#define MQTT_RECONNECT_INTERVAL 5000
#define ONLINE_CHECK_INTERVAL 30000 
#define FULL_THRESHOLD 90.0f
#define AIR_QUALITY_THRESHOLD 70
#define AIR_QUALITY_RAW_MIN 0
#define AIR_QUALITY_RAW_MAX 4095
#define TILT_THRESHOLD 25.0f
#define HUMAN_LEAVE_CLOSE_DELAY_MS 5000UL
#define TILT_CONFIRM_DELAY_MS 2000UL
#define FULL_CONFIRM_DELAY_MS 5000UL
#define FULL_RELEASE_DELAY_MS 5000UL
#define FULL_RELEASE_THRESHOLD 85.0f
#define FRONT_MANUAL_HOLD_MS 10000UL
#define FAN_MANUAL_OVERRIDE_MS 120000UL
#define MPU_CALIBRATION_SAMPLES 30
#define CONFIG_MAGIC 0x43424647UL
#define CONFIG_VERSION 1

typedef struct {
    uint32_t magic;
    uint8_t version;
    char wifiSsid[33];
    char wifiPass[65];
    char mqttServer[65];
    uint16_t mqttPort;
} DeviceConfig;

typedef enum {
    STATE_INIT,
    STATE_STANDBY,
    STATE_PUT_IN,
    STATE_FULL_LOCK,
    STATE_ALARM,
    STATE_MAINTENANCE,
    STATE_AP_MODE
} DeviceState;

typedef enum {
    ALERT_NONE,
    ALERT_BOX_FULL,
    ALERT_BOX_TILT,
    ALERT_PWD_ERROR,
    ALERT_AIR_BAD
} AlertType;

typedef struct {
    float capacity;
    float temperature;
    float humidity;
    uint16_t airQuality;
    bool humanDetect;
    bool boxTiltAlert;
    bool fanStatus;
    bool frontDoor;
    bool backDoor;
    char netMode[4];
} SensorData;

typedef struct {
    DeviceState state;
    AlertType currentAlert;
    char netMode[4];
    bool wifiConnected;
    bool mqttConnected;
    unsigned long lastOnlineTime;
} SystemStatus;

SensorData g_sensorData;
SystemStatus g_systemStatus;
DeviceConfig g_config;
WiFiClient g_wifiClient;
PubSubClient g_mqttClient(g_wifiClient);
U8G2_SH1106_128X64_NONAME_F_HW_I2C g_u8g2(U8G2_R0, U8X8_PIN_NONE);
WebServer g_configServer(80);

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
    {'D', 'C', 'B', 'A'},
    {'#', '9', '6', '3'},
    {'0', '8', '5', '2'},
    {'*', '7', '4', '1'}
};
byte rowPins[ROWS] = {PIN_KEY_R1, PIN_KEY_R2, PIN_KEY_R3, PIN_KEY_R4};
byte colPins[COLS] = {PIN_KEY_C1, PIN_KEY_C2, PIN_KEY_C3, PIN_KEY_C4};
Keypad g_keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

char g_passwordBuffer[MAX_PASSWORD_LEN + 1];
uint8_t g_passwordIndex = 0;
unsigned long g_passwordStartMs = 0;
bool g_passwordCorrect = false;

unsigned long g_lastSensorUpdate = 0;
unsigned long g_lastMqttPublish = 0;
unsigned long g_lastOledUpdate = 0;
unsigned long g_lastWifiCheck = 0;
unsigned long g_lastMqttCheck = 0;
unsigned long g_buzzUntilMs = 0;
unsigned long g_lastHumanSeenMs = 0;
unsigned long g_frontDoorAutoCloseAtMs = 0;
unsigned long g_tiltConfirmSinceMs = 0;
unsigned long g_fullConfirmSinceMs = 0;
unsigned long g_fullReleaseSinceMs = 0;
unsigned long g_frontManualUntilMs = 0;
unsigned long g_fanManualOverrideUntilMs = 0;
float g_lastTiltAngle = 0.0f;
float g_mpuPitchOffset = 0.0f;
float g_mpuRollOffset = 0.0f;
bool g_mpuCalibrated = false;
bool g_fullConfirmed = false;
bool g_prevHumanDetect = false;

bool readDht11(float &temp, float &hum);
float readDistanceCm();
int readMq135();
bool readMpu6050Raw(float &pitch, float &roll);
bool readMpu6050(float &angle);
void calibrateMpu6050();
bool isTimerActive(unsigned long untilMs);
uint32_t remainingMs(unsigned long untilMs);
void fanOn();
void fanOff();
void buzzerOn();
void buzzerOff();
void buzzerBeep(uint16_t ms = BUZZER_BEEP_MS);
void ledNormalOn();
void ledNormalOff();
void ledAlertOn();
void ledAlertOff();
void openFrontDoor();
void closeFrontDoor();
void openBackDoor();
void closeBackDoor();
void updateSensorData();
void updateSystemState();
void updateAutoFrontDoor();
void loadDeviceConfig();
void saveDeviceConfig();
void resetDeviceConfig();
void applyDeviceConfig(JsonDocument &doc, const char *source);
void publishTelemetry();
void publishAlert(AlertType type, const char *msg);
void executeCommand(const char *cmd, const char *source);
void handleMqttMessage(char *topic, byte *payload, unsigned int length);
void connectWifi();
void connectMqtt();
void setupApMode();
void setupConfigPortal();
void handleConfigPortal();
void handleLocalRequest(String path, String body);
void drawOled();
void handleSerialCommand();
void handleKeypad();
void httpServerLoop();
void printSnapshot(const char *source);
void sendCors();

void sendJsonWithCors(int code, const String &payload)
{
    sendCors();
    g_configServer.send(code, "application/json", payload);
}

String buildStatusJson()
{
    StaticJsonDocument<1536> doc;
    doc["deviceId"] = DEVICE_ID;
    doc["wifiSsid"] = g_config.wifiSsid;
    doc["mqttServer"] = g_config.mqttServer;
    doc["mqttPort"] = g_config.mqttPort;
    doc["wifiConnected"] = g_systemStatus.wifiConnected;
    doc["mqttConnected"] = g_systemStatus.mqttConnected;
    doc["netMode"] = g_systemStatus.netMode;
    doc["systemState"] = g_systemStatus.state == STATE_STANDBY ? "STANDBY" :
                          g_systemStatus.state == STATE_PUT_IN ? "PUT_IN" :
                          g_systemStatus.state == STATE_FULL_LOCK ? "FULL_LOCK" :
                          g_systemStatus.state == STATE_ALARM ? "ALARM" :
                          g_systemStatus.state == STATE_MAINTENANCE ? "MAINTENANCE" :
                          g_systemStatus.state == STATE_AP_MODE ? "AP_MODE" : "INIT";
    doc["staIp"] = WiFi.localIP().toString();
    doc["apIp"] = WiFi.softAPIP().toString();
    doc["capacity"] = g_sensorData.capacity;
    doc["temperature"] = g_sensorData.temperature;
    doc["humidity"] = g_sensorData.humidity;
    doc["airQuality"] = g_sensorData.airQuality;
    doc["humanDetect"] = g_sensorData.humanDetect;
    doc["boxTiltAlert"] = g_sensorData.boxTiltAlert;
    doc["tiltAngle"] = g_lastTiltAngle;
    doc["fanStatus"] = g_sensorData.fanStatus ? 1 : 0;
    doc["frontDoor"] = g_sensorData.frontDoor ? 1 : 0;
    doc["backDoor"] = g_sensorData.backDoor ? 1 : 0;
    doc["fullConfirmed"] = g_fullConfirmed ? 1 : 0;
    doc["fullConfirming"] = g_fullConfirmSinceMs != 0 && !g_fullConfirmed ? 1 : 0;
    doc["fullConfirmMs"] = g_fullConfirmSinceMs != 0 && !g_fullConfirmed ? (uint32_t)(millis() - g_fullConfirmSinceMs) : 0;
    doc["fullReleaseMs"] = g_fullReleaseSinceMs != 0 && g_fullConfirmed ? (uint32_t)(millis() - g_fullReleaseSinceMs) : 0;
    doc["frontManualHoldMs"] = remainingMs(g_frontManualUntilMs);
    doc["fanManualOverrideMs"] = remainingMs(g_fanManualOverrideUntilMs);
    doc["mpuCalibrated"] = g_mpuCalibrated ? 1 : 0;
    String out;
    serializeJson(doc, out);
    return out;
}
  bool readDht11(float &temp, float &hum)  
{
         uint8_t bits[5] =  
    {
        0
    }
    ;
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
         while (digitalRead(PIN_DHT11) == HIGH)  
    {
                 if (micros() - t > 100) return false;

    }
         t = micros();
         while (digitalRead(PIN_DHT11) == LOW)  
    {
                 if (micros() - t > 100) return false;

    }
         t = micros();
         while (digitalRead(PIN_DHT11) == HIGH)  
    {
                 if (micros() - t > 100) return false;

    }
          for (int i = 0;
     i < 40;
     i++)  
    {
                 t = micros();
                 while (digitalRead(PIN_DHT11) == LOW)  
        {
                         if (micros() - t > 100) return false;

        }
                 uint32_t highStart = micros();
                 while (digitalRead(PIN_DHT11) == HIGH)  
        {
                         if (micros() - highStart > 120) break;

        }
                 uint32_t highDuration = micros() - highStart;
                 uint8_t bitValue = (highDuration > 40) ? 1 : 0;
                  bits[byteIndex] <<= 1;
                 bits[byteIndex] |= bitValue;
                  if (bitIndex == 0)  
        {
                         bitIndex = 7;
                         byteIndex++;

        }
         else  
        {
                         bitIndex--;

        }

    }
          uint8_t sum = bits[0] + bits[1] + bits[2] + bits[3];
         if (sum != bits[4]) return false;
          hum = bits[0] + bits[1] / 10.0f;
         temp = bits[2] + bits[3] / 10.0f;
         return true;

}
  float readDistanceCm()  
{
         digitalWrite(PIN_TRIG, LOW);
         delayMicroseconds(2);
         digitalWrite(PIN_TRIG, HIGH);
         delayMicroseconds(10);
         digitalWrite(PIN_TRIG, LOW);
          unsigned long duration = pulseIn(PIN_ECHO, HIGH, 30000UL);
         if (duration == 0) return -1.0f;
          return duration * 0.0343f / 2.0f;

}
  int readMq135()  
{
         int raw = analogRead(PIN_MQ135);
         int percent = map(raw, AIR_QUALITY_RAW_MIN, AIR_QUALITY_RAW_MAX, 0, 100);
         if (percent < 0) percent = 0;
         if (percent > 100) percent = 100;
         Serial.printf("[SENSOR] air raw=%d percent=%d threshold=%d\n", raw, percent, AIR_QUALITY_THRESHOLD);
         return percent;

}
  bool readMpu6050Raw(float &pitch, float &roll)
{
         Wire.beginTransmission(MPU_ADDR);
         Wire.write(0x3B);
         if (Wire.endTransmission(false) != 0) return false;
          if (Wire.requestFrom(MPU_ADDR, (uint8_t)6, (uint8_t)true) != 6) return false;
          int16_t ax = (Wire.read() << 8) | Wire.read();
         int16_t ay = (Wire.read() << 8) | Wire.read();
         int16_t az = (Wire.read() << 8) | Wire.read();
          pitch = atan2((float)ay, sqrt((float)ax * (float)ax + (float)az * (float)az)) * 180.0f / PI;
          roll = atan2(-(float)ax, (float)az) * 180.0f / PI;
          return true;

}

  bool readMpu6050(float &angle)
{
         float pitch = 0.0f;
         float roll = 0.0f;
         if (!readMpu6050Raw(pitch, roll)) return false;
         if (g_mpuCalibrated) {
                 pitch -= g_mpuPitchOffset;
                 roll -= g_mpuRollOffset;
         }
         angle = max(abs(pitch), abs(roll));
         return true;

}

void calibrateMpu6050()
{
    float pitchSum = 0.0f;
    float rollSum = 0.0f;
    int okCount = 0;

    Serial.println("[MPU] calibrating baseline, keep box still");
    for (int i = 0; i < MPU_CALIBRATION_SAMPLES; i++) {
        float pitch = 0.0f;
        float roll = 0.0f;
        if (readMpu6050Raw(pitch, roll)) {
            pitchSum += pitch;
            rollSum += roll;
            okCount++;
        }
        delay(30);
    }

    if (okCount > 0) {
        g_mpuPitchOffset = pitchSum / okCount;
        g_mpuRollOffset = rollSum / okCount;
        g_mpuCalibrated = true;
        Serial.printf("[MPU] baseline pitch=%.2f roll=%.2f samples=%d\n", g_mpuPitchOffset, g_mpuRollOffset, okCount);
    } else {
        g_mpuCalibrated = false;
        g_mpuPitchOffset = 0.0f;
        g_mpuRollOffset = 0.0f;
        Serial.println("[MPU] calibration failed, using absolute angle");
    }
}

bool isTimerActive(unsigned long untilMs)
{
    return untilMs != 0 && (long)(untilMs - millis()) > 0;
}

uint32_t remainingMs(unsigned long untilMs)
{
    if (!isTimerActive(untilMs)) return 0;
    return (uint32_t)(untilMs - millis());
}

void fanOn()
{
    digitalWrite(PIN_FAN_IN1, HIGH);
    ledcWrite(PIN_FAN_ENA, 255);
    g_sensorData.fanStatus = true;
    Serial.println("[ACT] fan gpio on");
}

void fanOff()
{
    ledcWrite(PIN_FAN_ENA, 0);
    digitalWrite(PIN_FAN_IN1, LOW);
    g_sensorData.fanStatus = false;
    Serial.println("[ACT] fan gpio off");
}

void buzzerOn()
{
    digitalWrite(PIN_BUZZER, LOW);
    g_buzzUntilMs = 0;
    Serial.println("[ACT] buzzer on");
}

void buzzerOff()
{
    digitalWrite(PIN_BUZZER, HIGH);
    g_buzzUntilMs = 0;
    Serial.println("[ACT] buzzer off");
}

void buzzerBeep(uint16_t ms)
{
    digitalWrite(PIN_BUZZER, LOW);
    g_buzzUntilMs = millis() + ms;
    Serial.printf("[ACT] buzzer beep %u ms\n", ms);
}
void ledNormalOn()  
{
    Serial.println("[LED] normal on");
}
 void ledNormalOff()  
{
    Serial.println("[LED] normal off");
}
 void ledAlertOn()  
{
    digitalWrite(PIN_LED_ALERT, HIGH);
    Serial.println("[LED] alert on");
}
 void ledAlertOff()  
{
    digitalWrite(PIN_LED_ALERT, LOW);
    Serial.println("[LED] alert off");
}
void openFrontDoor()
{
    digitalWrite(PIN_FRONT_DOOR_LIGHT, HIGH);
    g_sensorData.frontDoor = true;
    Serial.println("[ACT] front door light on");
}

void closeFrontDoor()
{
    digitalWrite(PIN_FRONT_DOOR_LIGHT, LOW);
    g_sensorData.frontDoor = false;
    Serial.println("[ACT] front door light off");
}

void openBackDoor()
{
    digitalWrite(PIN_BACK_DOOR_LIGHT, HIGH);
    g_sensorData.backDoor = true;
    Serial.println("[ACT] back door light on");
}

void closeBackDoor()
{
    digitalWrite(PIN_BACK_DOOR_LIGHT, LOW);
    g_sensorData.backDoor = false;
    Serial.println("[ACT] back door light off");
}

void loadDeviceConfig()
{
    memset(&g_config, 0, sizeof(g_config));
    g_config.magic = CONFIG_MAGIC;
    g_config.version = CONFIG_VERSION;
    strncpy(g_config.wifiSsid, WIFI_SSID, sizeof(g_config.wifiSsid) - 1);
    strncpy(g_config.wifiPass, WIFI_PASS, sizeof(g_config.wifiPass) - 1);
    strncpy(g_config.mqttServer, MQTT_SERVER, sizeof(g_config.mqttServer) - 1);
    g_config.mqttPort = MQTT_PORT;
    saveDeviceConfig();
    Serial.println("[CFG] EEPROM cleared, using code defaults");
    Serial.printf("[CFG] wifi ssid=%s mqtt=%s:%u\n", g_config.wifiSsid, g_config.mqttServer, g_config.mqttPort);
}

void saveDeviceConfig()
{
    g_config.magic = CONFIG_MAGIC;
    g_config.version = CONFIG_VERSION;
    EEPROM.put(0, g_config);
    EEPROM.commit();
}

void resetDeviceConfig()
{
    memset(&g_config, 0, sizeof(g_config));
    g_config.magic = CONFIG_MAGIC;
    g_config.version = CONFIG_VERSION;
    strncpy(g_config.wifiSsid, WIFI_SSID, sizeof(g_config.wifiSsid) - 1);
    strncpy(g_config.wifiPass, WIFI_PASS, sizeof(g_config.wifiPass) - 1);
    strncpy(g_config.mqttServer, MQTT_SERVER, sizeof(g_config.mqttServer) - 1);
    g_config.mqttPort = MQTT_PORT;
    saveDeviceConfig();
    Serial.printf("[CFG] reset to default wifi=%s mqtt=%s:%u\n", g_config.wifiSsid, g_config.mqttServer, g_config.mqttPort);
}

void applyDeviceConfig(JsonDocument &doc, const char *source)
{
    const char *ssid = doc["wifiSsid"] | doc["ssid"] | doc["wifi_ssid"];
    const char *pass = doc["wifiPass"] | doc["password"] | doc["wifi_password"];
    const char *mqttServer = doc["mqttServer"] | doc["mqtt_server"];
    uint16_t mqttPort = doc["mqttPort"] | doc["mqtt_port"] | g_config.mqttPort;

    bool changed = false;
    if (ssid && strlen(ssid) > 0) {
        memset(g_config.wifiSsid, 0, sizeof(g_config.wifiSsid));
        strncpy(g_config.wifiSsid, ssid, sizeof(g_config.wifiSsid) - 1);
        changed = true;
    }
    if (pass) {
        memset(g_config.wifiPass, 0, sizeof(g_config.wifiPass));
        strncpy(g_config.wifiPass, pass, sizeof(g_config.wifiPass) - 1);
        changed = true;
    }
    if (mqttServer && strlen(mqttServer) > 0) {
        memset(g_config.mqttServer, 0, sizeof(g_config.mqttServer));
        strncpy(g_config.mqttServer, mqttServer, sizeof(g_config.mqttServer) - 1);
        changed = true;
    }
    if (mqttPort > 0 && mqttPort != g_config.mqttPort) {
        g_config.mqttPort = mqttPort;
        changed = true;
    }

    if (!changed) {
        Serial.printf("[%s] config unchanged\n", source);
        return;
    }

    saveDeviceConfig();
    Serial.printf("[%s] config saved wifi=%s mqtt=%s:%u\n", source, g_config.wifiSsid, g_config.mqttServer, g_config.mqttPort);

    if (g_mqttClient.connected()) {
        g_mqttClient.disconnect();
    }
    WiFi.disconnect();
    g_systemStatus.wifiConnected = false;
    g_systemStatus.mqttConnected = false;
    connectWifi();
    setupConfigPortal();
    if (g_systemStatus.wifiConnected) {
        connectMqtt();
    }
}
  void updateSensorData()  
{
         float temp, hum;
         if (readDht11(temp, hum))  
    {
                 g_sensorData.temperature = temp;
                 g_sensorData.humidity = hum;

    }
          float dist = readDistanceCm();
         if (dist > 0)  
    {
                 float maxDist = 60.0f;
                 float minDist = 5.0f;
                 float capacity = 0.0f;
                 if (dist < maxDist)  
        {
                         capacity = ((maxDist - dist) / (maxDist - minDist)) * 100.0f;

        }
                 if (capacity < 0) capacity = 0;
                 if (capacity > 100) capacity = 100;
                 g_sensorData.capacity = capacity;

    }
          g_sensorData.airQuality = readMq135();
         bool humanNow = (digitalRead(PIN_PIR) == HIGH);
         g_sensorData.humanDetect = humanNow;
         if (humanNow) {
                 g_lastHumanSeenMs = millis();
                 g_frontDoorAutoCloseAtMs = 0;
         } else if (g_prevHumanDetect && g_frontDoorAutoCloseAtMs == 0) {
                 g_frontDoorAutoCloseAtMs = millis() + HUMAN_LEAVE_CLOSE_DELAY_MS;
                 Serial.printf("[PIR] human left, front door closes in %lu ms\n", HUMAN_LEAVE_CLOSE_DELAY_MS);
         }
         g_prevHumanDetect = humanNow;
          float tiltAngle;
         if (readMpu6050(tiltAngle))  
    {
                 g_lastTiltAngle = tiltAngle;
                 Serial.printf("[SENSOR] tilt=%.2f threshold=%.2f\n", tiltAngle, TILT_THRESHOLD);
                 if (tiltAngle > TILT_THRESHOLD) {
                         if (g_tiltConfirmSinceMs == 0) g_tiltConfirmSinceMs = millis();
                         g_sensorData.boxTiltAlert = (millis() - g_tiltConfirmSinceMs) >= TILT_CONFIRM_DELAY_MS;
                 } else {
                         g_tiltConfirmSinceMs = 0;
                         g_sensorData.boxTiltAlert = false;
                 }

    }
         else {
                 g_sensorData.boxTiltAlert = false;
                 g_tiltConfirmSinceMs = 0;
         }
         printSnapshot("SENSOR");

}

void updateAutoFrontDoor()
{
    if (isTimerActive(g_frontManualUntilMs)) {
        g_frontDoorAutoCloseAtMs = 0;
        return;
    }

    if (g_sensorData.humanDetect) {
        g_frontDoorAutoCloseAtMs = 0;
        if (!g_sensorData.frontDoor && !g_fullConfirmed && g_systemStatus.state != STATE_FULL_LOCK) {
            openFrontDoor();
            g_systemStatus.state = STATE_PUT_IN;
            buzzerBeep(300);
            publishTelemetry();
            Serial.println("[PIR] human detected, front door light opened");
        }
        return;
    }

    if (g_sensorData.frontDoor) {
        if (g_frontDoorAutoCloseAtMs == 0) {
            g_frontDoorAutoCloseAtMs = millis() + HUMAN_LEAVE_CLOSE_DELAY_MS;
            Serial.printf("[PIR] human false, front door closes in %lu ms\n", HUMAN_LEAVE_CLOSE_DELAY_MS);
            return;
        }

        if (millis() >= g_frontDoorAutoCloseAtMs) {
            closeFrontDoor();
            g_frontDoorAutoCloseAtMs = 0;
            if (g_systemStatus.state == STATE_PUT_IN) {
                g_systemStatus.state = STATE_STANDBY;
            }
            publishTelemetry();
            Serial.println("[PIR] front door light auto closed");
        }
    } else {
        g_frontDoorAutoCloseAtMs = 0;
    }
}
void updateSystemState()
{
    updateAutoFrontDoor();

    if (g_sensorData.capacity >= FULL_THRESHOLD) {
        g_fullReleaseSinceMs = 0;
        if (g_fullConfirmSinceMs == 0) {
            g_fullConfirmSinceMs = millis();
            Serial.printf("[FULL] capacity %.1f >= %.1f, confirming\n", g_sensorData.capacity, FULL_THRESHOLD);
        }
        if (!g_fullConfirmed && millis() - g_fullConfirmSinceMs >= FULL_CONFIRM_DELAY_MS) {
            g_fullConfirmed = true;
            Serial.println("[FULL] confirmed full lock");
            publishTelemetry();
        }
    } else {
        g_fullConfirmSinceMs = 0;
    }

    if (g_fullConfirmed && g_sensorData.capacity <= FULL_RELEASE_THRESHOLD) {
        if (g_fullReleaseSinceMs == 0) {
            g_fullReleaseSinceMs = millis();
            Serial.printf("[FULL] capacity %.1f <= %.1f, confirming release\n", g_sensorData.capacity, FULL_RELEASE_THRESHOLD);
        }
        if (millis() - g_fullReleaseSinceMs >= FULL_RELEASE_DELAY_MS) {
            g_fullConfirmed = false;
            g_fullReleaseSinceMs = 0;
            Serial.println("[FULL] released full lock");
            publishTelemetry();
        }
    } else if (g_sensorData.capacity > FULL_RELEASE_THRESHOLD) {
        g_fullReleaseSinceMs = 0;
    }

    switch (g_systemStatus.state) {
        case STATE_INIT:
            g_systemStatus.state = STATE_STANDBY;
            break;

        case STATE_STANDBY:
            if (g_fullConfirmed) {
                g_systemStatus.state = STATE_FULL_LOCK;
                g_systemStatus.currentAlert = ALERT_BOX_FULL;
                if (g_sensorData.frontDoor) {
                    closeFrontDoor();
                    g_frontDoorAutoCloseAtMs = 0;
                }
                publishAlert(ALERT_BOX_FULL, "BOX_FULL: capacity over 90 percent");
                buzzerBeep(500);
                ledAlertOn();
            } else if (g_sensorData.boxTiltAlert) {
                g_systemStatus.state = STATE_ALARM;
                g_systemStatus.currentAlert = ALERT_BOX_TILT;
                publishAlert(ALERT_BOX_TILT, "BOX_TILT: box tilt detected");
                buzzerBeep(1000);
                ledAlertOn();
            } else if (g_sensorData.airQuality > AIR_QUALITY_THRESHOLD) {
                g_systemStatus.state = STATE_ALARM;
                g_systemStatus.currentAlert = ALERT_AIR_BAD;
                publishAlert(ALERT_AIR_BAD, "AIR_BAD: air quality percent over threshold");
                ledAlertOn();
                if (!isTimerActive(g_fanManualOverrideUntilMs)) {
                    fanOn();
                } else {
                    Serial.println("[FAN] air alarm active, manual override keeps fan state");
                }
                buzzerBeep(500);
            }
            break;

        case STATE_PUT_IN:
            if (!g_sensorData.frontDoor) {
                g_systemStatus.state = STATE_STANDBY;
            }
            break;

        case STATE_FULL_LOCK:
            if (!g_fullConfirmed) {
                g_systemStatus.currentAlert = ALERT_NONE;
                g_systemStatus.state = STATE_STANDBY;
                ledAlertOff();
            }
            break;

        case STATE_ALARM:
            if (!g_sensorData.boxTiltAlert && g_sensorData.airQuality <= AIR_QUALITY_THRESHOLD) {
                g_systemStatus.currentAlert = ALERT_NONE;
                g_systemStatus.state = STATE_STANDBY;
                ledAlertOff();
                if (!isTimerActive(g_fanManualOverrideUntilMs)) {
                    fanOff();
                }
                buzzerOff();
            }
            break;

        case STATE_MAINTENANCE:
        case STATE_AP_MODE:
        default:
            break;
    }
}
void publishTelemetry()
{
    if (!g_systemStatus.mqttConnected) {
        Serial.println("[MQTT] skip telemetry, mqtt disconnected");
        return;
    }

    StaticJsonDocument<1536> doc;
    doc["deviceId"] = DEVICE_ID;
    doc["timestamp"] = (uint32_t)(millis() / 1000);
    doc["capacity"] = g_sensorData.capacity;
    doc["temperature"] = g_sensorData.temperature;
    doc["humidity"] = g_sensorData.humidity;
    doc["airQuality"] = g_sensorData.airQuality;
    doc["humanDetect"] = g_sensorData.humanDetect;
    doc["boxTiltAlert"] = g_sensorData.boxTiltAlert;
    doc["tiltAngle"] = g_lastTiltAngle;
    doc["fanStatus"] = g_sensorData.fanStatus ? 1 : 0;
    doc["frontDoor"] = g_sensorData.frontDoor ? 1 : 0;
    doc["backDoor"] = g_sensorData.backDoor ? 1 : 0;
    doc["fullConfirmed"] = g_fullConfirmed ? 1 : 0;
    doc["fullConfirming"] = g_fullConfirmSinceMs != 0 && !g_fullConfirmed ? 1 : 0;
    doc["fullConfirmMs"] = g_fullConfirmSinceMs != 0 && !g_fullConfirmed ? (uint32_t)(millis() - g_fullConfirmSinceMs) : 0;
    doc["fullReleaseMs"] = g_fullReleaseSinceMs != 0 && g_fullConfirmed ? (uint32_t)(millis() - g_fullReleaseSinceMs) : 0;
    doc["frontManualHoldMs"] = remainingMs(g_frontManualUntilMs);
    doc["fanManualOverrideMs"] = remainingMs(g_fanManualOverrideUntilMs);
    doc["mpuCalibrated"] = g_mpuCalibrated ? 1 : 0;
    doc["netMode"] = g_systemStatus.netMode;
    doc["systemState"] = g_systemStatus.state == STATE_STANDBY ? "STANDBY" :
                          g_systemStatus.state == STATE_PUT_IN ? "PUT_IN" :
                          g_systemStatus.state == STATE_FULL_LOCK ? "FULL_LOCK" :
                          g_systemStatus.state == STATE_ALARM ? "ALARM" :
                          g_systemStatus.state == STATE_MAINTENANCE ? "MAINTENANCE" :
                          g_systemStatus.state == STATE_AP_MODE ? "AP_MODE" : "INIT";
    doc["wifiSsid"] = g_config.wifiSsid;
    doc["mqttServer"] = g_config.mqttServer;
    doc["mqttPort"] = g_config.mqttPort;
    doc["staIp"] = WiFi.localIP().toString();

    char buffer[1536];
    size_t len = serializeJson(doc, buffer, sizeof(buffer));
    bool ok = g_mqttClient.publish("device/clothes_box/telemetry", buffer, len);
    Serial.printf("[MQTT] telemetry publish %s len=%u\n", ok ? "ok" : "fail", (unsigned)len);
    Serial.printf("[MQTT] telemetry %s\n", buffer);
    printSnapshot("MQTT");
}

void publishAlert(AlertType type, const char *msg)
{
    if (!g_systemStatus.mqttConnected) {
        Serial.println("[MQTT] skip alert, mqtt disconnected");
        return;
    }

    StaticJsonDocument<256> doc;
    doc["alertType"] = type == ALERT_BOX_FULL ? "BOX_FULL" :
                       type == ALERT_BOX_TILT ? "BOX_TILT" :
                       type == ALERT_PWD_ERROR ? "PWD_ERROR" : "AIR_BAD";
    doc["alertMsg"] = msg;

    char buffer[256];
    size_t len = serializeJson(doc, buffer, sizeof(buffer));
    bool ok = g_mqttClient.publish("device/clothes_box/alert", buffer, len);
    Serial.printf("[MQTT] alert publish %s len=%u\n", ok ? "ok" : "fail", (unsigned)len);
    Serial.printf("[MQTT] alert %s\n", buffer);
}

void executeCommand(const char *cmd, const char *source)
{
    if (!cmd || strlen(cmd) == 0) {
        Serial.printf("[%s] empty command\n", source);
        return;
    }

    Serial.printf("[%s] cmd=%s\n", source, cmd);

    if (strcmp(cmd, "RESET_CONFIG") == 0 || strcmp(cmd, "RESETCFG") == 0) {
        resetDeviceConfig();
        if (g_mqttClient.connected()) {
            g_mqttClient.disconnect();
        }
        WiFi.disconnect();
        g_systemStatus.wifiConnected = false;
        g_systemStatus.mqttConnected = false;
        connectWifi();
        if (g_systemStatus.wifiConnected) {
            connectMqtt();
        }
    } else if (strcmp(cmd, "OPEN_FRONT") == 0 || strcmp(cmd, "FRONT_ON") == 0 || strcmp(cmd, "ON_FRONT") == 0) {
        g_frontManualUntilMs = millis() + FRONT_MANUAL_HOLD_MS;
        g_frontDoorAutoCloseAtMs = 0;
        if (!g_fullConfirmed && g_systemStatus.state != STATE_FULL_LOCK) {
            openFrontDoor();
            buzzerBeep(200);
            publishTelemetry();
        } else {
            Serial.printf("[%s] rejected OPEN_FRONT, box full lock\n", source);
        }
    } else if (strcmp(cmd, "CLOSE_FRONT") == 0 || strcmp(cmd, "FRONT_OFF") == 0 || strcmp(cmd, "OFF_FRONT") == 0) {
        g_frontManualUntilMs = millis() + FRONT_MANUAL_HOLD_MS;
        g_frontDoorAutoCloseAtMs = 0;
        closeFrontDoor();
        publishTelemetry();
    } else if (strcmp(cmd, "OPEN_BACK") == 0 || strcmp(cmd, "BACK_ON") == 0 || strcmp(cmd, "ON_BACK") == 0) {
        openBackDoor();
        buzzerBeep(200);
        publishTelemetry();
    } else if (strcmp(cmd, "CLOSE_BACK") == 0 || strcmp(cmd, "BACK_OFF") == 0 || strcmp(cmd, "OFF_BACK") == 0) {
        closeBackDoor();
        publishTelemetry();
    } else if (strcmp(cmd, "FAN_ON") == 0) {
        g_fanManualOverrideUntilMs = millis() + FAN_MANUAL_OVERRIDE_MS;
        fanOn();
        publishTelemetry();
    } else if (strcmp(cmd, "FAN_OFF") == 0) {
        g_fanManualOverrideUntilMs = millis() + FAN_MANUAL_OVERRIDE_MS;
        fanOff();
        publishTelemetry();
    } else if (strcmp(cmd, "BUZZER_ON") == 0 || strcmp(cmd, "BEEP_ON") == 0) {
        buzzerOn();
    } else if (strcmp(cmd, "BUZZER_OFF") == 0 || strcmp(cmd, "BEEP_OFF") == 0) {
        buzzerOff();
    } else if (strcmp(cmd, "BUZZER_BEEP") == 0 || strcmp(cmd, "BEEP") == 0) {
        buzzerBeep(500);
    } else if (strcmp(cmd, "ALARM_STOP") == 0 || strcmp(cmd, "CANCEL_ALARM") == 0) {
        g_systemStatus.currentAlert = ALERT_NONE;
        g_systemStatus.state = STATE_STANDBY;
        ledAlertOff();
        fanOff();
        buzzerOff();
        publishTelemetry();
        Serial.println("[ACT] alarm stop");
    } else if (strcmp(cmd, "STATUS") == 0) {
        Serial.printf("[STATUS] front=%d back=%d fan=%d cap=%.1f temp=%.1f hum=%.1f air=%u tilt=%.1f full=%d frontHoldMs=%lu fanOverrideMs=%lu mpuCal=%d wifi=%d mqtt=%d\n",
                      g_sensorData.frontDoor ? 1 : 0,
                      g_sensorData.backDoor ? 1 : 0,
                      g_sensorData.fanStatus ? 1 : 0,
                      g_sensorData.capacity,
                      g_sensorData.temperature,
                      g_sensorData.humidity,
                      g_sensorData.airQuality,
                      g_lastTiltAngle,
                      g_fullConfirmed ? 1 : 0,
                      (unsigned long)remainingMs(g_frontManualUntilMs),
                      (unsigned long)remainingMs(g_fanManualOverrideUntilMs),
                      g_mpuCalibrated ? 1 : 0,
                      g_systemStatus.wifiConnected ? 1 : 0,
                      g_systemStatus.mqttConnected ? 1 : 0);
    } else {
        Serial.printf("[%s] unknown command: %s\n", source, cmd);
    }
}

void handleMqttMessage(char *topic, byte *payload, unsigned int length)
{
    String msg;
    msg.reserve(length + 1);
    for (unsigned int i = 0; i < length; i++) {
        msg += (char)payload[i];
    }

    Serial.printf("[MQTT] recv topic=%s payload=%s\n", topic, msg.c_str());

    StaticJsonDocument<256> doc;
    DeserializationError error = deserializeJson(doc, msg);
    if (error) {
        msg.trim();
        msg.toUpperCase();
        executeCommand(msg.c_str(), "MQTT");
        return;
    }

    const char *cmd = doc["cmd"] | doc["action"] | doc["command"];
    if (strcmp(topic, "device/clothes_box/config") == 0) {
        applyDeviceConfig(doc, "MQTT");
        return;
    }
    if (!cmd) {
        Serial.println("[MQTT] missing cmd/action/command");
        return;
    }

    String command = String(cmd);
    command.trim();
    command.toUpperCase();
    executeCommand(command.c_str(), "MQTT");
}

void connectWifi()
{
    if (WiFi.status() == WL_CONNECTED) {
        g_systemStatus.wifiConnected = true;
        strcpy(g_systemStatus.netMode, "STA");
        if (g_systemStatus.state == STATE_AP_MODE) {
            g_systemStatus.state = STATE_STANDBY;
        }
        return;
    }

    Serial.println("[WiFi] connecting...");
    WiFi.mode(WIFI_AP_STA);
    WiFi.begin(g_config.wifiSsid, g_config.wifiPass);

    unsigned long start = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - start < 8000) {
        delay(500);
        Serial.print(".");
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println();
        Serial.println("[WiFi] connected");
        Serial.print("[WiFi] ip=");
        Serial.println(WiFi.localIP());
        g_systemStatus.wifiConnected = true;
        strcpy(g_systemStatus.netMode, "STA");
        if (g_systemStatus.state == STATE_AP_MODE) {
            g_systemStatus.state = STATE_STANDBY;
        }
    } else {
        Serial.println();
        Serial.println("[WiFi] failed, keep AP offline mode");
        g_systemStatus.wifiConnected = false;
        g_systemStatus.mqttConnected = false;
        if (g_systemStatus.state != STATE_AP_MODE) {
            setupApMode();
        }
    }
}

void connectMqtt()
{
    if (!g_systemStatus.wifiConnected) {
        Serial.println("[MQTT] skip connect, wifi disconnected");
        return;
    }

    if (g_mqttClient.connected()) {
        g_systemStatus.mqttConnected = true;
        return;
    }

    g_mqttClient.setServer(g_config.mqttServer, g_config.mqttPort);
    g_mqttClient.setCallback(handleMqttMessage);
    g_mqttClient.setKeepAlive(60);
    g_mqttClient.setSocketTimeout(10);
    g_mqttClient.setBufferSize(1024);
    g_systemStatus.mqttConnected = false;

    Serial.printf("[MQTT] connecting %s:%u ...\n", g_config.mqttServer, g_config.mqttPort);
    if (g_mqttClient.connect(DEVICE_ID, MQTT_USER, MQTT_PASS)) {
        Serial.println("[MQTT] connected");
        g_mqttClient.subscribe("device/clothes_box/control");
        g_mqttClient.subscribe("device/clothes_box/config");
        g_systemStatus.mqttConnected = true;
        Serial.println("[MQTT] subscribed device/clothes_box/control");
        Serial.println("[MQTT] subscribed device/clothes_box/config");
    } else {
        Serial.print("[MQTT] failed rc=");
        Serial.println(g_mqttClient.state());
        g_systemStatus.mqttConnected = false;
    }
}

void setupApMode()
{
    WiFi.mode(WIFI_AP_STA);
    IPAddress apIP(192, 168, 4, 1);
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
    WiFi.softAP(AP_SSID, AP_PASS);
    setupConfigPortal();

    Serial.println("[WiFi] AP offline mode started");
    Serial.print("[WiFi] AP ip=");
    Serial.println(WiFi.softAPIP());

    strcpy(g_systemStatus.netMode, "AP");
    g_systemStatus.state = STATE_AP_MODE;
    g_systemStatus.wifiConnected = false;
    g_systemStatus.mqttConnected = false;
}

void sendCors()
{
    g_configServer.sendHeader("Access-Control-Allow-Origin", "*");
    g_configServer.sendHeader("Access-Control-Allow-Methods", "GET,POST,OPTIONS");
    g_configServer.sendHeader("Access-Control-Allow-Headers", "Content-Type");
}

void setupConfigPortal()
{
    static bool started = false;
    if (started) return;
    started = true;

    g_configServer.on("/", HTTP_GET, []() {
        sendCors();
        g_configServer.send(200, "text/html",
            "<!doctype html><meta charset='utf-8'><title>CLOTHES_BOX_AP</title>"
            "<h2>CLOTHES_BOX_AP Config</h2>"
            "<p>Use /api/local/status, /api/local/networks, /api/local/config</p>");
    });

    g_configServer.on("/api/local/status", HTTP_OPTIONS, []() { sendCors(); g_configServer.send(204); });
    g_configServer.on("/api/local/control", HTTP_OPTIONS, []() { sendCors(); g_configServer.send(204); });
    g_configServer.on("/api/local/fan", HTTP_OPTIONS, []() { sendCors(); g_configServer.send(204); });
    g_configServer.on("/api/local/unlock", HTTP_OPTIONS, []() { sendCors(); g_configServer.send(204); });
    g_configServer.on("/api/local/switch_mode", HTTP_OPTIONS, []() { sendCors(); g_configServer.send(204); });
    g_configServer.on("/api/local/config", HTTP_OPTIONS, []() { sendCors(); g_configServer.send(204); });
    g_configServer.on("/api/local/networks", HTTP_OPTIONS, []() { sendCors(); g_configServer.send(204); });

    g_configServer.on("/api/local/status", HTTP_GET, []() {
        sendJsonWithCors(200, buildStatusJson());
    });

    g_configServer.on("/api/local/control", HTTP_POST, []() {
        StaticJsonDocument<512> doc;
        DeserializationError err = deserializeJson(doc, g_configServer.arg("plain"));
        if (err) {
            sendJsonWithCors(400, "{\"code\":400,\"msg\":\"bad json\"}");
            return;
        }

        const char *actionRaw = doc["action"] | doc["cmd"] | doc["command"] | "";
        String action = String(actionRaw);
        action.trim();
        action.toUpperCase();
        if (action.length() == 0) {
            sendJsonWithCors(400, "{\"code\":400,\"msg\":\"缺少action\"}");
            return;
        }

        executeCommand(action.c_str(), "HTTP_LOCAL");
        publishTelemetry();
        String out = String("{\"code\":200,\"msg\":\"ok\",\"data\":{\"sent\":true,\"action\":\"") + action + "\"}}";
        sendJsonWithCors(200, out);
    });

    g_configServer.on("/api/local/fan", HTTP_POST, []() {
        StaticJsonDocument<256> doc;
        DeserializationError err = deserializeJson(doc, g_configServer.arg("plain"));
        if (err) {
            sendJsonWithCors(400, "{\"code\":400,\"msg\":\"bad json\"}");
            return;
        }

        String action;
        if (doc["state"] | false) {
            action = "FAN_ON";
        } else {
            const char *fanRaw = doc["action"] | doc["cmd"] | "";
            String v = String(fanRaw);
            v.trim();
            v.toUpperCase();
            action = (v == "ON" || v == "FAN_ON") ? "FAN_ON" : "FAN_OFF";
        }

        executeCommand(action.c_str(), "HTTP_LOCAL");
        publishTelemetry();
        String out = String("{\"code\":200,\"msg\":\"ok\",\"data\":{\"sent\":true,\"action\":\"") + action + "\"}}";
        sendJsonWithCors(200, out);
    });

    g_configServer.on("/api/local/unlock", HTTP_POST, []() {
        StaticJsonDocument<256> doc;
        DeserializationError err = deserializeJson(doc, g_configServer.arg("plain"));
        if (err) {
            sendJsonWithCors(400, "{\"code\":400,\"msg\":\"bad json\"}");
            return;
        }

        const char *pwd = doc["pwd"] | doc["password"] | doc["unlockPassword"] | "";
        if (strcmp(pwd, ADMIN_PASSWORD) != 0) {
            sendJsonWithCors(401, "{\"code\":401,\"msg\":\"密码错误\"}");
            return;
        }

        openBackDoor();
        g_passwordCorrect = true;
        g_systemStatus.state = STATE_MAINTENANCE;
        buzzerBeep(300);
        publishTelemetry();
        sendJsonWithCors(200, "{\"code\":200,\"msg\":\"ok\",\"data\":{\"sent\":true,\"unlocked\":true}}");
    });

    g_configServer.on("/api/local/switch_mode", HTTP_POST, []() {
        StaticJsonDocument<256> doc;
        DeserializationError err = deserializeJson(doc, g_configServer.arg("plain"));
        if (err) {
            sendJsonWithCors(400, "{\"code\":400,\"msg\":\"bad json\"}");
            return;
        }

        const char *modeRaw = doc["targetMode"] | doc["mode"] | doc["netMode"] | "";
        String targetMode = String(modeRaw);
        targetMode.trim();
        targetMode.toUpperCase();

        if (targetMode == "AP") {
            setupApMode();
        } else if (targetMode == "STA") {
            connectWifi();
            if (g_systemStatus.wifiConnected) {
                connectMqtt();
            }
        } else {
            sendJsonWithCors(400, "{\"code\":400,\"msg\":\"invalid targetMode\"}");
            return;
        }

        publishTelemetry();
        String out = String("{\"code\":200,\"msg\":\"ok\",\"data\":{\"sent\":true,\"currentNetMode\":\"") + targetMode + "\"}}";
        sendJsonWithCors(200, out);
    });

    g_configServer.on("/api/local/networks", HTTP_GET, []() {
        int count = WiFi.scanNetworks();
        StaticJsonDocument<1024> doc;
        JsonArray arr = doc.createNestedArray("networks");
        for (int i = 0; i < count && i < 20; i++) {
            JsonObject item = arr.createNestedObject();
            item["ssid"] = WiFi.SSID(i);
            item["rssi"] = WiFi.RSSI(i);
            item["secure"] = WiFi.encryptionType(i) != WIFI_AUTH_OPEN;
        }
        String out;
        serializeJson(doc, out);
        sendCors();
        g_configServer.send(200, "application/json", out);
    });

    g_configServer.on("/api/local/config", HTTP_POST, []() {
        StaticJsonDocument<512> doc;
        DeserializationError err = deserializeJson(doc, g_configServer.arg("plain"));
        sendCors();
        if (err) {
            g_configServer.send(400, "application/json", "{\"success\":false,\"msg\":\"bad json\"}");
            return;
        }
        applyDeviceConfig(doc, "AP");
        g_configServer.send(200, "application/json", "{\"success\":true,\"msg\":\"config saved, reconnecting\"}");
    });

    g_configServer.begin();
    Serial.println("[AP] config portal ready http://192.168.4.1");
}

void handleConfigPortal()
{
    g_configServer.handleClient();
}
  void handleLocalRequest(String path, String body)  
{
         Serial.print("Local request: ");
         Serial.println(path);
          if (path == "/api/local/status")  
    {
                 StaticJsonDocument<1536> doc;
                 doc["capacity"] = g_sensorData.capacity;
                 doc["temperature"] = g_sensorData.temperature;
                 doc["humidity"] = g_sensorData.humidity;
                 doc["airQuality"] = g_sensorData.airQuality;
                 doc["humanDetect"] = g_sensorData.humanDetect;
                 doc["boxTiltAlert"] = g_sensorData.boxTiltAlert;
                 doc["tiltAngle"] = g_lastTiltAngle;
                 doc["fanStatus"] = g_sensorData.fanStatus ? 1 : 0;
                 doc["frontDoor"] = g_sensorData.frontDoor ? 1 : 0;
                 doc["backDoor"] = g_sensorData.backDoor ? 1 : 0;
                 doc["fullConfirmed"] = g_fullConfirmed ? 1 : 0;
                 doc["fullConfirming"] = g_fullConfirmSinceMs != 0 && !g_fullConfirmed ? 1 : 0;
                 doc["fullConfirmMs"] = g_fullConfirmSinceMs != 0 && !g_fullConfirmed ? (uint32_t)(millis() - g_fullConfirmSinceMs) : 0;
                 doc["fullReleaseMs"] = g_fullReleaseSinceMs != 0 && g_fullConfirmed ? (uint32_t)(millis() - g_fullReleaseSinceMs) : 0;
                 doc["frontManualHoldMs"] = remainingMs(g_frontManualUntilMs);
                 doc["fanManualOverrideMs"] = remainingMs(g_fanManualOverrideUntilMs);
                 doc["mpuCalibrated"] = g_mpuCalibrated ? 1 : 0;
                 doc["netMode"] = g_systemStatus.netMode;
                  char buffer[1536];
                 serializeJson(doc, buffer, sizeof(buffer));
                  Serial.println("HTTP/1.1 200 OK");
                 Serial.println("Content-Type: application/json");
                 Serial.println("Access-Control-Allow-Origin: *");
                 Serial.println("");
                 Serial.println(buffer);

    }
     else if (path == "/api/local/unlock")  
    {
                 StaticJsonDocument<256> doc;
                 DeserializationError error = deserializeJson(doc, body);
                          if (!error && doc["password"])  
        {
                         String password = doc["password"].as<String>();
                         if (password == ADMIN_PASSWORD)  
            {
                                 openBackDoor();
                                 g_passwordCorrect = true;
                                 g_systemStatus.state = STATE_MAINTENANCE;
                                 buzzerBeep(300);
                                 publishTelemetry();
                                                  Serial.println("HTTP/1.1 200 OK");
                                 Serial.println("Content-Type: application/json");
                                 Serial.println("Access-Control-Allow-Origin: *");
                                 Serial.println("");
                                  Serial.println("{\"success\":true,\"msg\":\"Local admin password verified, back door unlocked\"}");

            }
             else  
            {
                                 buzzerBeep(500);
                                 g_systemStatus.currentAlert = ALERT_PWD_ERROR;
                                                  Serial.println("HTTP/1.1 401 Unauthorized");
                                 Serial.println("Content-Type: application/json");
                                 Serial.println("Access-Control-Allow-Origin: *");
                                 Serial.println("");
                                  Serial.println("{\"success\":false,\"msg\":\"Password error\"}");

            }

        }
         else  
        {
                         Serial.println("HTTP/1.1 400 Bad Request");
                         Serial.println("Content-Type: application/json");
                         Serial.println("Access-Control-Allow-Origin: *");
                         Serial.println("");
                          Serial.println("{\"success\":false,\"msg\":\"Password error\"}");

        }

    }
     else  
    {
                 Serial.println("HTTP/1.1 404 Not Found");
                 Serial.println("Content-Type: text/plain");
                 Serial.println("");
                 Serial.println("Not Found");

    }

}
  void httpServerLoop()  
{
         if (strcmp(g_systemStatus.netMode, "AP") != 0) return;
          if (Serial.available() > 0)  
     {
                 String line = Serial.readStringUntil('\n');
                 line.trim();
                 if (line.startsWith("GET ") || line.startsWith("POST "))  
        {
                         int space1 = line.indexOf(' ');
                         int space2 = line.indexOf(' ', space1 + 1);
                         String method = line.substring(0, space1);
                         String path = line.substring(space1 + 1, space2);
                          String body = "";
                         if (method == "POST")  
            {
                                 while (!Serial.available()) delay(1);
                                 body = Serial.readStringUntil('\n');
                                 body.trim();

            }
                          handleLocalRequest(path, body);

        }

    }

}
void drawOled()  
{
         g_u8g2.clearBuffer();
         g_u8g2.setFont(u8g2_font_6x12_tr);
          char line1[32];
         char line2[32];
         char line3[32];
         char line4[32];
          snprintf(line1, sizeof(line1), "ID:%s", DEVICE_ID);
         snprintf(line2, sizeof(line2), "T:%.1fC H:%.1f%%", g_sensorData.temperature, g_sensorData.humidity);
         snprintf(line3, sizeof(line3), "CAP:%.0f%% AIR:%u%% FULL:%d", g_sensorData.capacity, g_sensorData.airQuality, g_fullConfirmed ? 1 : 0);
              const char *stateStr = "INIT";
         switch (g_systemStatus.state)  
    {
                 case STATE_STANDBY: stateStr = "STANDBY";
         break;
                 case STATE_PUT_IN: stateStr = "PUTTING";
         break;
                 case STATE_FULL_LOCK: stateStr = "FULL";
         break;
                 case STATE_ALARM: stateStr = "ALARM";
         break;
                 case STATE_MAINTENANCE: stateStr = "MAINT";
         break;
                 case STATE_AP_MODE: stateStr = "AP MODE";
         break;
                 default: break;

    }
         snprintf(line4, sizeof(line4), "%s F%d B%d V%d", stateStr, g_sensorData.frontDoor ? 1 : 0, g_sensorData.backDoor ? 1 : 0, g_sensorData.fanStatus ? 1 : 0);
          g_u8g2.drawStr(0, 14, line1);
         g_u8g2.drawStr(0, 30, line2);
         g_u8g2.drawStr(0, 46, line3);
         g_u8g2.drawStr(0, 62, line4);
          g_u8g2.sendBuffer();

}

void printSnapshot(const char *source)
{
    Serial.printf("[%s] DEV=%s NET=%s STATE=%d T=%.1fC H=%.1f%% CAP=%.1f%% AIR=%u%% TILT=%.1f FAN=%d FRONT=%d BACK=%d HUMAN=%d TILT_ALERT=%d FULL=%d FRONT_HOLD_MS=%lu FAN_OVERRIDE_MS=%lu MPU_CAL=%d WIFI=%d MQTT=%d\n",
                  source,
                  DEVICE_ID,
                  g_systemStatus.netMode,
                  (int)g_systemStatus.state,
                  g_sensorData.temperature,
                  g_sensorData.humidity,
                  g_sensorData.capacity,
                  g_sensorData.airQuality,
                  g_lastTiltAngle,
                  g_sensorData.fanStatus ? 1 : 0,
                  g_sensorData.frontDoor ? 1 : 0,
                  g_sensorData.backDoor ? 1 : 0,
                  g_sensorData.humanDetect ? 1 : 0,
                  g_sensorData.boxTiltAlert ? 1 : 0,
                  g_fullConfirmed ? 1 : 0,
                  (unsigned long)remainingMs(g_frontManualUntilMs),
                  (unsigned long)remainingMs(g_fanManualOverrideUntilMs),
                  g_mpuCalibrated ? 1 : 0,
                  g_systemStatus.wifiConnected ? 1 : 0,
                  g_systemStatus.mqttConnected ? 1 : 0);
}

void handleSerialCommand()
{
    if (!Serial.available()) {
        return;
    }

    String line;
    unsigned long start = millis();
    while (millis() - start < 200) {
        while (Serial.available()) {
            char c = (char)Serial.read();
            if (c == '\r' || c == '\n') {
                line.trim();
                if (line.length() == 0) {
                    return;
                }
                if (line.startsWith("GET ") || line.startsWith("POST ")) {
                    return;
                }
                line.toUpperCase();
                executeCommand(line.c_str(), "SERIAL");
                return;
            }
            line += c;
            if (line.length() >= 96) {
                line.trim();
                if (line.startsWith("GET ") || line.startsWith("POST ")) {
                    return;
                }
                line.toUpperCase();
                executeCommand(line.c_str(), "SERIAL");
                return;
            }
        }
        delay(1);
    }

    line.trim();
    if (line.length() == 0) return;
    if (line.startsWith("GET ") || line.startsWith("POST ")) return;
    line.toUpperCase();
    executeCommand(line.c_str(), "SERIAL");
}

  void handleKeypad()  
{
         char key = g_keypad.getKey();
         if (key != NO_KEY)  
    {
                 Serial.print("Key pressed: ");
                 Serial.println(key);
                 if (key == 'D') {
                     if (g_passwordCorrect || g_systemStatus.state == STATE_MAINTENANCE) {
                         if (g_sensorData.backDoor) {
                             g_passwordCorrect = false;
                             g_systemStatus.state = STATE_STANDBY;
                             executeCommand("CLOSE_BACK", "KEYPAD");
                             Serial.println("[KEYPAD] maintenance door closed, admin session ended");
                         } else {
                             g_passwordCorrect = true;
                             g_systemStatus.state = STATE_MAINTENANCE;
                             executeCommand("OPEN_BACK", "KEYPAD");
                             Serial.println("[KEYPAD] maintenance door opened by admin");
                         }
                     } else {
                         buzzerBeep(300);
                         Serial.println("[KEYPAD] D ignored, enter admin password then # first");
                     }
                     return;
                 }
                 if (key == 'C') {
                     executeCommand("ALARM_STOP", "KEYPAD");
                     return;
                 }
                 if (key == 'B') {
                     executeCommand("FAN_ON", "KEYPAD");
                     return;
                 }
                 if (key == 'A') {
                     executeCommand("FAN_OFF", "KEYPAD");
                     return;
                 }
                  if (g_passwordIndex == 0)  
        {
                         g_passwordStartMs = millis();

        }
                  if (key == '#')  
        {
                         if (strcmp(g_passwordBuffer, ADMIN_PASSWORD) == 0)  
            {
                                 g_passwordCorrect = true;
                                  g_systemStatus.state = STATE_MAINTENANCE;
                                  openBackDoor();
                                  buzzerBeep(300);
                                  ledNormalOn();
                                  publishTelemetry();
                                  Serial.println("Password correct, entering maintenance mode");

            }
             else  
            {
                                 buzzerBeep(500);
                                 g_systemStatus.currentAlert = ALERT_PWD_ERROR;
                                 publishAlert(ALERT_PWD_ERROR, "Local password error");
                                 ledAlertOn();
                                                  Serial.println("Password incorrect");

            }
                         g_passwordIndex = 0;
                         memset(g_passwordBuffer, 0, sizeof(g_passwordBuffer));

        }
         else if (key == '*')  
        {
                         g_passwordIndex = 0;
                         memset(g_passwordBuffer, 0, sizeof(g_passwordBuffer));

        }
         else if (g_passwordIndex < MAX_PASSWORD_LEN)  
        {
                         g_passwordBuffer[g_passwordIndex++] = key;
                         g_passwordBuffer[g_passwordIndex] = '\0';
                         buzzerBeep(50);

        }

    }
          if (g_passwordIndex > 0 && millis() - g_passwordStartMs > PASSWORD_TIMEOUT)  
    {
                 g_passwordIndex = 0;
                 memset(g_passwordBuffer, 0, sizeof(g_passwordBuffer));
                 Serial.println("Password timeout");

    }

}
void setup()
{
    Serial.begin(115200);
    delay(500);
    Serial.println("System starting...");

    EEPROM.begin(512);
    loadDeviceConfig();

    pinMode(PIN_DHT11, INPUT_PULLUP);
    pinMode(PIN_MQ135, INPUT);
    pinMode(PIN_TRIG, OUTPUT);
    pinMode(PIN_ECHO, INPUT);
    pinMode(PIN_PIR, INPUT);
    pinMode(PIN_BUZZER, OUTPUT);
    pinMode(PIN_LED_NORMAL, OUTPUT);
    pinMode(PIN_LED_ALERT, OUTPUT);
    pinMode(PIN_FRONT_DOOR_LIGHT, OUTPUT);
    pinMode(PIN_BACK_DOOR_LIGHT, OUTPUT);
    pinMode(PIN_FAN_ENA, OUTPUT);
    pinMode(PIN_FAN_IN1, OUTPUT);

    digitalWrite(PIN_TRIG, LOW);
    digitalWrite(PIN_BUZZER, HIGH);
    digitalWrite(PIN_LED_NORMAL, LOW);
    digitalWrite(PIN_LED_ALERT, LOW);
    digitalWrite(PIN_FRONT_DOOR_LIGHT, LOW);
    digitalWrite(PIN_BACK_DOOR_LIGHT, LOW);
    digitalWrite(PIN_FAN_IN1, LOW);

    ledcAttach(PIN_FAN_ENA, FAN_PWM_FREQ, FAN_PWM_RES);
    ledcWrite(PIN_FAN_ENA, 0);

    analogReadResolution(12);
    analogSetPinAttenuation(PIN_MQ135, ADC_11db);

    Wire.begin(PIN_MPU_SDA, PIN_MPU_SCL);
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x6B);
    Wire.write(0x00);
    Wire.endTransmission(true);
    delay(100);
    calibrateMpu6050();

    g_u8g2.setI2CAddress(OLED_ADDR << 1);
    g_u8g2.begin();

    g_systemStatus.state = STATE_INIT;
    strcpy(g_systemStatus.netMode, "STA");
    g_systemStatus.currentAlert = ALERT_NONE;
    g_systemStatus.wifiConnected = false;
    g_systemStatus.mqttConnected = false;

    memset(g_passwordBuffer, 0, sizeof(g_passwordBuffer));
    g_passwordIndex = 0;
    g_passwordCorrect = false;

    g_sensorData.capacity = 0;
    g_sensorData.temperature = 0;
    g_sensorData.humidity = 0;
    g_sensorData.airQuality = 0;
    g_sensorData.humanDetect = false;
    g_sensorData.boxTiltAlert = false;
    g_sensorData.fanStatus = false;
    g_sensorData.frontDoor = false;
    g_sensorData.backDoor = false;
    g_fullConfirmed = false;
    g_fullConfirmSinceMs = 0;
    g_fullReleaseSinceMs = 0;
    g_frontManualUntilMs = 0;
    g_fanManualOverrideUntilMs = 0;

    connectWifi();
    if (g_systemStatus.wifiConnected) {
        connectMqtt();
    }

    ledNormalOn();
    Serial.println("System ready");
}

void loop()
{
    handleConfigPortal();

    if (g_buzzUntilMs != 0 && millis() >= g_buzzUntilMs) {
        digitalWrite(PIN_BUZZER, HIGH);
        g_buzzUntilMs = 0;
    }

    bool wifiNow = (WiFi.status() == WL_CONNECTED);
    if (!wifiNow && g_systemStatus.wifiConnected) {
        Serial.println("[WiFi] lost connection");
        g_systemStatus.wifiConnected = false;
        g_systemStatus.mqttConnected = false;
        setupApMode();
    } else if (wifiNow && !g_systemStatus.wifiConnected) {
        Serial.println("[WiFi] connection restored");
        g_systemStatus.wifiConnected = true;
        strcpy(g_systemStatus.netMode, "STA");
        if (g_systemStatus.state == STATE_AP_MODE) {
            g_systemStatus.state = STATE_STANDBY;
        }
    }

    if (!g_systemStatus.wifiConnected && g_systemStatus.state != STATE_AP_MODE && millis() - g_lastWifiCheck > WIFI_RECONNECT_INTERVAL) {
        g_lastWifiCheck = millis();
        connectWifi();
    }

    if (g_systemStatus.wifiConnected) {
        if (!g_mqttClient.connected()) {
            if (g_systemStatus.mqttConnected) {
                Serial.println("[MQTT] lost connection");
            }
            g_systemStatus.mqttConnected = false;
            if (millis() - g_lastMqttCheck > MQTT_RECONNECT_INTERVAL) {
                g_lastMqttCheck = millis();
                connectMqtt();
            }
        } else {
            g_systemStatus.mqttConnected = true;
            g_mqttClient.loop();
        }

        if (g_systemStatus.mqttConnected && millis() - g_lastMqttPublish > MQTT_PUBLISH_INTERVAL) {
            g_lastMqttPublish = millis();
            publishTelemetry();
        }
    }

    if (strcmp(g_systemStatus.netMode, "AP") == 0) {
        httpServerLoop();
    }

    if (millis() - g_lastSensorUpdate > SENSOR_UPDATE_INTERVAL) {
        g_lastSensorUpdate = millis();
        updateSensorData();
        updateSystemState();
    }

    if (millis() - g_lastOledUpdate > OLED_UPDATE_INTERVAL) {
        g_lastOledUpdate = millis();
        drawOled();
    }

    handleSerialCommand();
    handleKeypad();
    delay(10);
}



