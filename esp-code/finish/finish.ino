#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <EEPROM.h>
#include <Keypad.h>
#include <U8g2lib.h>

#define WIFI_SSID "hhhhhh"
#define WIFI_PASS "huangyaru"
#define MQTT_SERVER "192.168.246.1"
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
#define PIN_ECHO 4
#define PIN_PIR 16
#define PIN_MPU_SDA 21
#define PIN_MPU_SCL 22
#define PIN_OLED_SDA 21
#define PIN_OLED_SCL 22
#define PIN_BUZZER 5
#define PIN_LED_NORMAL 14
#define PIN_LED_ALERT 12
#define PIN_FAN_ENA 27
#define PIN_FAN_IN1 15
#define PIN_KEY_R1 18
#define PIN_KEY_R2 19
#define PIN_KEY_R3 23
#define PIN_KEY_R4 32
#define PIN_KEY_C1 25
#define PIN_KEY_C2 26
#define PIN_KEY_C3 13
#define PIN_KEY_C4 33

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
#define ONLINE_CHECK_INTERVAL 30000

#define FULL_THRESHOLD 90.0f
#define AIR_QUALITY_THRESHOLD 300
#define TILT_THRESHOLD 30.0f

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

WiFiClient g_wifiClient;
PubSubClient g_mqttClient(g_wifiClient);

U8G2_SH1106_128X64_NONAME_F_HW_I2C g_u8g2(U8G2_R0, U8X8_PIN_NONE);

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
    {'1', '4', '7', '*'},
    {'2', '5', '8', '0'},
    {'3', '6', '9', '#'},
    {'A', 'B', 'C', 'D'}
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
unsigned long g_buzzUntilMs = 0;

bool readDht11(float &temp, float &hum);
float readDistanceCm();
int readMq135();
bool readMpu6050(float &angle);
void fanOn();
void fanOff();
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
void publishTelemetry();
void publishAlert(AlertType type, const char *msg);
void handleMqttMessage(char *topic, byte *payload, unsigned int length);
void connectWifi();
void connectMqtt();
void setupApMode();
void handleLocalRequest(String path, String body);
void drawOled();
void handleKeypad();
void httpServerLoop();

bool readDht11(float &temp, float &hum) {
    uint8_t bits[5] = {0};
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

    uint8_t sum = bits[0] + bits[1] + bits[2] + bits[3];
    if (sum != bits[4]) return false;

    hum = bits[0] + bits[1] / 10.0f;
    temp = bits[2] + bits[3] / 10.0f;
    return true;
}

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

int readMq135() {
    return analogRead(PIN_MQ135);
}

bool readMpu6050(float &angle) {
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x3B);
    if (Wire.endTransmission(false) != 0) return false;

    if (Wire.requestFrom(MPU_ADDR, (uint8_t)6, (uint8_t)true) != 6) return false;

    int16_t ax = (Wire.read() << 8) | Wire.read();
    int16_t ay = (Wire.read() << 8) | Wire.read();
    int16_t az = (Wire.read() << 8) | Wire.read();

    float pitch = atan2(ay, sqrt(ax * ax + az * az)) * 180.0f / PI;
    float roll = atan2(-ax, az) * 180.0f / PI;
    angle = max(abs(pitch), abs(roll));
    return true;
}

void fanOn() {
    digitalWrite(PIN_FAN_IN1, HIGH);
    ledcWrite(PIN_FAN_ENA, 255);
    g_sensorData.fanStatus = true;
}

void fanOff() {
    ledcWrite(PIN_FAN_ENA, 0);
    digitalWrite(PIN_FAN_IN1, LOW);
    g_sensorData.fanStatus = false;
}

void buzzerBeep(uint16_t ms) {
    digitalWrite(PIN_BUZZER, LOW);
    g_buzzUntilMs = millis() + ms;
}

void ledNormalOn() { digitalWrite(PIN_LED_NORMAL, HIGH); }
void ledNormalOff() { digitalWrite(PIN_LED_NORMAL, LOW); }
void ledAlertOn() { digitalWrite(PIN_LED_ALERT, HIGH); }
void ledAlertOff() { digitalWrite(PIN_LED_ALERT, LOW); }

void openFrontDoor() {
    g_sensorData.frontDoor = true;
}

void closeFrontDoor() {
    g_sensorData.frontDoor = false;
}

void openBackDoor() {
    g_sensorData.backDoor = true;
}

void closeBackDoor() {
    g_sensorData.backDoor = false;
}

void updateSensorData() {
    float temp, hum;
    if (readDht11(temp, hum)) {
        g_sensorData.temperature = temp;
        g_sensorData.humidity = hum;
    }

    float dist = readDistanceCm();
    if (dist > 0) {
        float maxDist = 60.0f;
        float minDist = 5.0f;
        float capacity = 0.0f;
        if (dist < maxDist) {
            capacity = ((maxDist - dist) / (maxDist - minDist)) * 100.0f;
        }
        if (capacity < 0) capacity = 0;
        if (capacity > 100) capacity = 100;
        g_sensorData.capacity = capacity;
    }

    g_sensorData.airQuality = readMq135();
    g_sensorData.humanDetect = (digitalRead(PIN_PIR) == HIGH);

    float tiltAngle;
    if (readMpu6050(tiltAngle)) {
        g_sensorData.boxTiltAlert = (tiltAngle > TILT_THRESHOLD);
    }
}

void updateSystemState() {
    switch (g_systemStatus.state) {
        case STATE_INIT:
            g_systemStatus.state = STATE_STANDBY;
            break;

        case STATE_STANDBY:
            if (g_sensorData.capacity >= FULL_THRESHOLD) {
                g_systemStatus.state = STATE_FULL_LOCK;
                g_systemStatus.currentAlert = ALERT_BOX_FULL;
                publishAlert(ALERT_BOX_FULL, "回收箱满载率超过90%，请及时清运");
                buzzerBeep(500);
                ledAlertOn();
            } else if (g_sensorData.boxTiltAlert) {
                g_systemStatus.state = STATE_ALARM;
                g_systemStatus.currentAlert = ALERT_BOX_TILT;
                publishAlert(ALERT_BOX_TILT, "箱体倾斜/倾倒异常，请检查");
                buzzerBeep(1000);
                ledAlertOn();
            } else if (g_sensorData.airQuality > AIR_QUALITY_THRESHOLD) {
                g_systemStatus.state = STATE_ALARM;
                g_systemStatus.currentAlert = ALERT_AIR_BAD;
                publishAlert(ALERT_AIR_BAD, "箱内空气质量异常，异味超标");
                fanOn();
                buzzerBeep(500);
            } else if (g_sensorData.humanDetect) {
                g_systemStatus.state = STATE_PUT_IN;
                openFrontDoor();
                buzzerBeep(300);
            }
            break;

        case STATE_PUT_IN:
            if (!g_sensorData.humanDetect) {
                delay(3000);
                closeFrontDoor();
                g_systemStatus.state = STATE_STANDBY;
            }
            break;

        case STATE_FULL_LOCK:
            if (g_sensorData.capacity < FULL_THRESHOLD) {
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
                fanOff();
            }
            break;

        case STATE_MAINTENANCE:
            break;

        case STATE_AP_MODE:
            break;

        default:
            break;
    }
}

void publishTelemetry() {
    if (!g_systemStatus.mqttConnected) return;

    StaticJsonDocument<512> doc;
    doc["deviceId"] = DEVICE_ID;
    doc["timestamp"] = (uint32_t)(millis() / 1000);
    doc["capacity"] = g_sensorData.capacity;
    doc["temperature"] = g_sensorData.temperature;
    doc["humidity"] = g_sensorData.humidity;
    doc["airQuality"] = g_sensorData.airQuality;
    doc["humanDetect"] = g_sensorData.humanDetect;
    doc["boxTiltAlert"] = g_sensorData.boxTiltAlert;
    doc["fanStatus"] = g_sensorData.fanStatus ? 1 : 0;
    doc["frontDoor"] = g_sensorData.frontDoor ? 1 : 0;
    doc["backDoor"] = g_sensorData.backDoor ? 1 : 0;
    doc["netMode"] = g_systemStatus.netMode;

    char buffer[512];
    serializeJson(doc, buffer, sizeof(buffer));
    g_mqttClient.publish("device/clothes_box/telemetry", buffer);
}

void publishAlert(AlertType type, const char *msg) {
    if (!g_systemStatus.mqttConnected) return;

    StaticJsonDocument<256> doc;
    doc["alertType"] = type == ALERT_BOX_FULL ? "BOX_FULL" : 
                       type == ALERT_BOX_TILT ? "BOX_TILT" :
                       type == ALERT_PWD_ERROR ? "PWD_ERROR" : "AIR_BAD";
    doc["alertMsg"] = msg;

    char buffer[256];
    serializeJson(doc, buffer, sizeof(buffer));
    g_mqttClient.publish("device/clothes_box/alert", buffer);
}

void handleMqttMessage(char *topic, byte *payload, unsigned int length) {
    payload[length] = '\0';
    String msg = String((char *)payload);

    StaticJsonDocument<256> doc;
    DeserializationError error = deserializeJson(doc, msg);
    if (error) return;

    const char *cmd = doc["cmd"];
    if (!cmd) return;

    if (strcmp(cmd, "OPEN_FRONT") == 0) {
        if (g_systemStatus.state != STATE_FULL_LOCK) {
            openFrontDoor();
            buzzerBeep(200);
        }
    } else if (strcmp(cmd, "CLOSE_FRONT") == 0) {
        closeFrontDoor();
    } else if (strcmp(cmd, "OPEN_BACK") == 0) {
        openBackDoor();
        buzzerBeep(200);
    } else if (strcmp(cmd, "CLOSE_BACK") == 0) {
        closeBackDoor();
    } else if (strcmp(cmd, "FAN_ON") == 0) {
        fanOn();
    } else if (strcmp(cmd, "FAN_OFF") == 0) {
        fanOff();
    } else if (strcmp(cmd, "ALARM_STOP") == 0) {
        g_systemStatus.currentAlert = ALERT_NONE;
        g_systemStatus.state = STATE_STANDBY;
        ledAlertOff();
        fanOff();
    }
}

void connectWifi() {
    Serial.println("Connecting to WiFi...");
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    unsigned long start = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - start < 15000) {
        delay(500);
        Serial.print(".");
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("");
        Serial.println("WiFi connected");
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
        g_systemStatus.wifiConnected = true;
        strcpy(g_systemStatus.netMode, "STA");
    } else {
        Serial.println("");
        Serial.println("WiFi connection failed, switching to AP mode");
        g_systemStatus.wifiConnected = false;
        setupApMode();
    }
}

void connectMqtt() {
    if (!g_systemStatus.wifiConnected) return;

    g_mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
    g_mqttClient.setCallback(handleMqttMessage);

    while (!g_mqttClient.connected()) {
        Serial.print("Connecting to MQTT...");
        if (g_mqttClient.connect(DEVICE_ID, MQTT_USER, MQTT_PASS)) {
            Serial.println("connected");
            g_mqttClient.subscribe("device/clothes_box/control");
            g_systemStatus.mqttConnected = true;
        } else {
            Serial.print("failed, rc=");
            Serial.print(g_mqttClient.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
}

void setupApMode() {
    WiFi.mode(WIFI_AP);
    IPAddress apIP(192, 168, 4, 1);
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
    WiFi.softAP(AP_SSID, AP_PASS);

    Serial.println("AP mode started");
    Serial.print("AP IP address: ");
    Serial.println(WiFi.softAPIP());

    strcpy(g_systemStatus.netMode, "AP");
    g_systemStatus.state = STATE_AP_MODE;
    g_systemStatus.wifiConnected = false;
    g_systemStatus.mqttConnected = false;
}

void handleLocalRequest(String path, String body) {
    Serial.print("Local request: ");
    Serial.println(path);

    if (path == "/api/local/status") {
        StaticJsonDocument<512> doc;
        doc["capacity"] = g_sensorData.capacity;
        doc["temperature"] = g_sensorData.temperature;
        doc["humidity"] = g_sensorData.humidity;
        doc["airQuality"] = g_sensorData.airQuality;
        doc["fanStatus"] = g_sensorData.fanStatus ? 1 : 0;
        doc["frontDoor"] = g_sensorData.frontDoor ? 1 : 0;
        doc["backDoor"] = g_sensorData.backDoor ? 1 : 0;

        char buffer[512];
        serializeJson(doc, buffer, sizeof(buffer));

        Serial.println("HTTP/1.1 200 OK");
        Serial.println("Content-Type: application/json");
        Serial.println("Access-Control-Allow-Origin: *");
        Serial.println("");
        Serial.println(buffer);
    } else if (path == "/api/local/unlock") {
        StaticJsonDocument<256> doc;
        DeserializationError error = deserializeJson(doc, body);
        
        if (!error && doc["password"]) {
            String password = doc["password"].as<String>();
            if (password == ADMIN_PASSWORD) {
                openBackDoor();
                buzzerBeep(300);
                
                Serial.println("HTTP/1.1 200 OK");
                Serial.println("Content-Type: application/json");
                Serial.println("Access-Control-Allow-Origin: *");
                Serial.println("");
                Serial.println("{\"success\":true,\"msg\":\"本地管理员密码校验通过，维护后门已解锁\"}");
            } else {
                buzzerBeep(500);
                g_systemStatus.currentAlert = ALERT_PWD_ERROR;
                
                Serial.println("HTTP/1.1 401 Unauthorized");
                Serial.println("Content-Type: application/json");
                Serial.println("Access-Control-Allow-Origin: *");
                Serial.println("");
                Serial.println("{\"success\":false,\"msg\":\"密码错误\"}");
            }
        } else {
            Serial.println("HTTP/1.1 400 Bad Request");
            Serial.println("Content-Type: application/json");
            Serial.println("Access-Control-Allow-Origin: *");
            Serial.println("");
            Serial.println("{\"success\":false,\"msg\":\"参数错误\"}");
        }
    } else {
        Serial.println("HTTP/1.1 404 Not Found");
        Serial.println("Content-Type: text/plain");
        Serial.println("");
        Serial.println("Not Found");
    }
}

void httpServerLoop() {
    if (strcmp(g_systemStatus.netMode, "AP") != 0) return;

    if (Serial.available() > 0) {
        String line = Serial.readStringUntil('\r');
        if (line.startsWith("GET ") || line.startsWith("POST ")) {
            int space1 = line.indexOf(' ');
            int space2 = line.indexOf(' ', space1 + 1);
            String method = line.substring(0, space1);
            String path = line.substring(space1 + 1, space2);

            String body = "";
            if (method == "POST") {
                while (!Serial.available()) delay(1);
                body = Serial.readStringUntil('\r');
            }

            handleLocalRequest(path, body);
        }
    }
}

void drawOled() {
    g_u8g2.clearBuffer();
    g_u8g2.setFont(u8g2_font_6x12_tr);

    char line1[24];
    char line2[24];
    char line3[24];
    char line4[24];

    snprintf(line1, sizeof(line1), "ID:%s", DEVICE_ID);
    snprintf(line2, sizeof(line2), "T:%.1fC H:%.1f%%", g_sensorData.temperature, g_sensorData.humidity);
    snprintf(line3, sizeof(line3), "CAP:%.0f%% AIR:%d", g_sensorData.capacity, g_sensorData.airQuality);
    
    const char *stateStr = "INIT";
    switch (g_systemStatus.state) {
        case STATE_STANDBY: stateStr = "STANDBY"; break;
        case STATE_PUT_IN: stateStr = "PUTTING"; break;
        case STATE_FULL_LOCK: stateStr = "FULL"; break;
        case STATE_ALARM: stateStr = "ALARM"; break;
        case STATE_MAINTENANCE: stateStr = "MAINT"; break;
        case STATE_AP_MODE: stateStr = "AP MODE"; break;
        default: break;
    }
    snprintf(line4, sizeof(line4), "%s %s", g_systemStatus.netMode, stateStr);

    g_u8g2.drawStr(0, 14, line1);
    g_u8g2.drawStr(0, 30, line2);
    g_u8g2.drawStr(0, 46, line3);
    g_u8g2.drawStr(0, 62, line4);

    g_u8g2.sendBuffer();
}

void handleKeypad() {
    char key = g_keypad.getKey();
    if (key != NO_KEY) {
        Serial.print("Key pressed: ");
        Serial.println(key);

        if (g_passwordIndex == 0) {
            g_passwordStartMs = millis();
        }

        if (key == '#') {
            if (strcmp(g_passwordBuffer, ADMIN_PASSWORD) == 0) {
                g_passwordCorrect = true;
                g_systemStatus.state = STATE_MAINTENANCE;
                openBackDoor();
                buzzerBeep(300);
                ledNormalOn();
                Serial.println("Password correct, entering maintenance mode");
            } else {
                buzzerBeep(500);
                g_systemStatus.currentAlert = ALERT_PWD_ERROR;
                publishAlert(ALERT_PWD_ERROR, "本地密码错误");
                Serial.println("Password incorrect");
            }
            g_passwordIndex = 0;
            memset(g_passwordBuffer, 0, sizeof(g_passwordBuffer));
        } else if (key == '*') {
            g_passwordIndex = 0;
            memset(g_passwordBuffer, 0, sizeof(g_passwordBuffer));
        } else if (g_passwordIndex < MAX_PASSWORD_LEN) {
            g_passwordBuffer[g_passwordIndex++] = key;
            g_passwordBuffer[g_passwordIndex] = '\0';
            buzzerBeep(50);
        }
    }

    if (g_passwordIndex > 0 && millis() - g_passwordStartMs > PASSWORD_TIMEOUT) {
        g_passwordIndex = 0;
        memset(g_passwordBuffer, 0, sizeof(g_passwordBuffer));
        Serial.println("Password timeout");
    }
}

void setup() {
    Serial.begin(115200);
    delay(500);
    Serial.println("System starting...");

    EEPROM.begin(512);

    pinMode(PIN_DHT11, INPUT_PULLUP);
    pinMode(PIN_MQ135, INPUT);
    pinMode(PIN_TRIG, OUTPUT);
    pinMode(PIN_ECHO, INPUT);
    pinMode(PIN_PIR, INPUT);
    pinMode(PIN_BUZZER, OUTPUT);
    pinMode(PIN_LED_NORMAL, OUTPUT);
    pinMode(PIN_LED_ALERT, OUTPUT);
    pinMode(PIN_FAN_ENA, OUTPUT);
    pinMode(PIN_FAN_IN1, OUTPUT);

    digitalWrite(PIN_TRIG, LOW);
    digitalWrite(PIN_BUZZER, HIGH);
    digitalWrite(PIN_LED_NORMAL, LOW);
    digitalWrite(PIN_LED_ALERT, LOW);
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

    connectWifi();
    if (g_systemStatus.wifiConnected) {
        connectMqtt();
    }

    ledNormalOn();
    Serial.println("System ready");
}

void loop() {
    if (g_systemStatus.buzzUntilMs != 0 && millis() >= g_systemStatus.buzzUntilMs) {
        digitalWrite(PIN_BUZZER, HIGH);
        g_systemStatus.buzzUntilMs = 0;
    }

    if (strcmp(g_systemStatus.netMode, "STA") == 0) {
        if (!g_systemStatus.wifiConnected) {
            if (millis() - g_lastWifiCheck > WIFI_RECONNECT_INTERVAL) {
                g_lastWifiCheck = millis();
                connectWifi();
            }
        } else {
            if (!g_systemStatus.mqttConnected) {
                connectMqtt();
            } else {
                g_mqttClient.loop();
            }

            if (millis() - g_lastMqttPublish > MQTT_PUBLISH_INTERVAL) {
                g_lastMqttPublish = millis();
                publishTelemetry();
            }
        }
    } else {
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

    handleKeypad();

    delay(10);
}