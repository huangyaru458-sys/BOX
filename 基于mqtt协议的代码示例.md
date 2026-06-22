/*
 * 示例程序 6-22：ESP32 MQTT基础发布与订阅
 * 主题规划：
 *   发布：esp32/<MAC后6位>/data     → 上报温湿度数据
 *   订阅：esp32/<MAC后6位>/control  → 接收控制指令
 */

#include <WiFi.h>
#include <PubSubClient.h>
#include "log_config.h"

#define TAG     "MQTT"
#define LED_PIN 2

const char* ssid       = "Wokwi-GUEST";
const char* password   = "";
const char* mqttBroker = "broker.emqx.io";
const int   mqttPort   = 1883;

char clientId[32], pubTopic[64], subTopic[64];

NetworkClient   networkClient;
PubSubClient    mqttClient(networkClient);

unsigned long lastPublishTime = 0;
const long    publishInterval = 10000;
volatile bool isConnected = false;

// WiFi 事件回调函数
void onWiFiEvent(WiFiEvent_t event) {
    switch (event) {
        case ARDUINO_EVENT_WIFI_STA_GOT_IP:
            LOG_I(TAG, "WiFi 已就绪，IP 地址: %s", WiFi.localIP().toString().c_str());
            isConnected = true;
            break;
        case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
            LOG_W(TAG, "WiFi 断开连接");
            isConnected = false;
            break;
        default:
            break;
    }
}

// MQTT 连接逻辑 (非阻塞尝试)
void connectMQTT() {
    if (!isConnected) return; // 没网络就不尝试

​    LOG_I(TAG, "正在尝试连接 MQTT...");
​    if (mqttClient.connect(clientId)) {
​        LOG_I(TAG, "MQTT 已连接");
​        mqttClient.subscribe(subTopic, 1);
​    } else {
​        LOG_E(TAG, "连接失败, 状态码=%d", mqttClient.state());
​    }
}

// MQTT 消息回调
void onMessageReceived(char* topic, byte* payload, unsigned int length) {
    String msg = String((char*)payload).substring(0, length);
    
    LOG_I(TAG, "收到主题 [%s] 的消息: %s", topic, msg.c_str());
    if (msg=="led_on") digitalWrite(LED_PIN, HIGH);
    else if (msg == "led_off") digitalWrite(LED_PIN, LOW);
}

void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    // 配置WiFi
    WiFi.onEvent(onWiFiEvent);
    WiFi.mode(WIFI_STA);
    WiFi.setAutoReconnect(true);
    WiFi.begin(ssid, password);
    // 生成设备 ID 和主题
    uint8_t mac[6];
    WiFi.macAddress(mac);
    snprintf(clientId, sizeof(clientId), "esp32_%02X%02X%02X", mac[3], mac[4], mac[5]);
    snprintf(pubTopic, sizeof(pubTopic), "esp32/%02X%02X%02X/data", mac[3], mac[4], mac[5]);
    snprintf(subTopic, sizeof(subTopic), "esp32/%02X%02X%02X/control", mac[3], mac[4], mac[5]);
    LOG_I(TAG,"发布主题：%s，订阅主题：%s",pubTopic,subTopic);

​    //  配置 MQTT
​    mqttClient.setServer(mqttBroker, mqttPort);
​    mqttClient.setCallback(onMessageReceived);
​    mqttClient.setBufferSize(512);

​    LOG_I(TAG, "系统初始化完成，等待 WiFi 连接...");
}

void loop() {
    mqttClient.loop();   // 保持 MQTT 心跳

​    unsigned long now = millis();
​    
​    // 如果连接掉线，每 5 秒尝试重连一次 (非阻塞)
​    if (!mqttClient.connected()) {
​        static unsigned long lastRetry = 0;
​        if (now - lastRetry > 5000) {
​            lastRetry = now;
​            connectMQTT();
​        }
​    } else {
​        // 仅在连接成功时进行定时发布
​        if (now - lastPublishTime >= publishInterval) {
​            lastPublishTime = now;
​            
​            float temp = 20.0 + random(0, 100) / 10.0;
​            char payload[128];
​            snprintf(payload, sizeof(payload), "{\"temp\":%.1f}", temp);
​            
​            mqttClient.publish(pubTopic, payload);
​            LOG_I(TAG, "数据已上报: %s", payload);
​        }
​    }
}

/*
 * 示例程序 6-23：MQTT遗嘱消息实现设备离线检测
 * 功能：
 *   1. 连接时注册遗嘱，异常掉线后Broker自动发布"offline"
 *   2. 正常连接后主动发布保留消息"online"
 *   3. 订阅状态主题，感知设备上下线事件
 * 主题规划：
 *   esp32/<MAC后6位>/status → 在线状态（"online"/"offline"，保留消息）
 */
#include <WiFi.h>
#include <PubSubClient.h>
#include "log_config.h"

#define TAG "MQTT_LWT"

const char* ssid       = "Wokwi-GUEST";
const char* password   = "";
const char* mqttBroker = "broker.emqx.io";
const int   mqttPort   = 1883;

char clientId[32], statusTopic[64];

NetworkClient   networkClient;
PubSubClient    mqttClient(networkClient);

unsigned long lastPublishTime = 0;
const long    publishInterval = 10000;
volatile bool isConnected = false;

// MQTT 消息回调
void onMessageReceived(char* topic, byte* payload, unsigned int length) {
    String msg = String((char*)payload).substring(0, length);
    LOG_I(TAG, "收到主题 [%s] 的消息: %s", topic, msg.c_str());
}

// MQTT 连接逻辑
void connectMQTT() {
    if (!isConnected) return; // 没网络就不尝试

​    LOG_I(TAG, "正在尝试连接 MQTT...");

​    bool ok = mqttClient.connect(
​        clientId,       // 客户端ID
​        nullptr,        // 用户名（匿名）
​        nullptr,        // 密码（匿名）
​        statusTopic,    // 遗嘱主题
​        1,              // 遗嘱QoS = 1
​        true,           // 遗嘱保留 = true
​        "offline"       // 遗嘱内容
​    );   
​    if (ok) {
​        LOG_I(TAG, "MQTT 已连接");
​        // 发布保留消息"online",
​        // Broker保存此消息，新订阅者订阅时立即收到当前在线状态
​        mqttClient.publish(statusTopic, "online", true /* retained */);
​        LOG_I(TAG, "已发布上线状态 -> %s: online", statusTopic);
​        // 订阅状态主题，感知设备上下线变化
​        mqttClient.subscribe(statusTopic, 1);
​    } else {
​        LOG_E(TAG, "连接失败, 状态码=%d", mqttClient.state());
​    }
}

// WiFi 事件回调函数
void onWiFiEvent(WiFiEvent_t event) {
    switch (event) {
        case ARDUINO_EVENT_WIFI_STA_GOT_IP:
            LOG_I(TAG, "WiFi 已就绪，IP 地址: %s", WiFi.localIP().toString().c_str());
            isConnected = true;
            break;
        case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
            LOG_W(TAG, "WiFi 断开连接");
            isConnected = false;
            break;
        default:
            break;
    }
}

void setup() {
    Serial.begin(115200);

​    // 配置WiFi
​    WiFi.onEvent(onWiFiEvent);
​    WiFi.mode(WIFI_STA);
​    WiFi.setAutoReconnect(true);
​    WiFi.begin(ssid, password);
​    // 生成设备 ID 和主题
​    uint8_t mac[6];
​    WiFi.macAddress(mac);
​    snprintf(clientId,sizeof(clientId),"esp32_%02X%02X%02X", mac[3], mac[4], mac[5]);
​    snprintf(statusTopic, sizeof(statusTopic),"esp32/%02X%02X%02X/status", mac[3], mac[4], mac[5]);
​    LOG_I(TAG,"状态主题：%s",statusTopic);

​    //  配置 MQTT
​    mqttClient.setServer(mqttBroker, mqttPort);
​    mqttClient.setCallback(onMessageReceived);
​    mqttClient.setBufferSize(512);

​    LOG_I(TAG, "系统初始化完成，等待 WiFi 连接...");
}

void loop() {
    mqttClient.loop();   // 保持 MQTT 心跳

​    unsigned long now = millis();

​    if (!mqttClient.connected()) {
​        static unsigned long lastRetry = 0;
​        if (now - lastRetry > 5000 || lastRetry==0) {
​            lastRetry = now;
​            connectMQTT();
​        }
​    }
}

/*
 * 示例程序 6-24：MQTT over TLS（MQTTS）安全连接
 * 功能：通过TLS加密连接EMQ公共Broker的8883端口
 * 说明：rootCACert 需替换为目标Broker实际的根CA证书内容
 */
 #include <WiFi.h>
 #include <NetworkClientSecure.h>
 #include <PubSubClient.h>
 #include "log_config.h"

#define TAG "MQTTS_EVENT"

const char* ssid       = "Wokwi-GUEST";
const char* password   = "";
const char* mqttBroker = "broker.emqx.io";
const int   mqttPort   = 8883;

// 根 CA 证书
const char* rootCACert = R"rawliteral(
-----BEGIN CERTIFICATE-----
MIIDrzCCApegAwIBAgIQCDvgVpBCRrGhdWrJWZHHSjANBgkqhkiG9w0BAQUFADBh
MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3
d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBD
QTAeFw0wNjExMTAwMDAwMDBaFw0zMTExMTAwMDAwMDBaMGExCzAJBgNVBAYTAlVT
MRUwEwYDVQQKEwxEaWdpQ2VydCBJbmMxGTAXBgNVBAsTEHd3dy5kaWdpY2VydC5j
b20xIDAeBgNVBAMTF0RpZ2lDZXJ0IEdsb2JhbCBSb290IENBMIIBIjANBgkqhkiG
9w0BAQEFAAOCAQ8AMIIBCgKCAQEA4jvhEXLeqKTTo1eqUKKPC3eQyaKl7hLOllsB
CSDMAZOnTjC3U/dDxGkAV53ijSLdhwZAAIEJzs4bg7/fzTtxRuLWZscFs3YnFo97
nh6Vfe63SKMI2tavegw5BmV/Sl0fvBf4q77uKNd0f3p4mVmFaG5cIzJLv07A6Fpt
43C/dxC//AH2hdmoRBBYMql1GNXRor5H4idq9Joz+EkIYIvUX7Q6hL+hqkpMfT7P
T19sdl6gSzeRntwi5m3OFBqOasv+zbMUZBfHWymeMr/y7vrTC0LUq7dBMtoM1O/4
gdW7jVg/tRvoSSiicNoxBN33shbyTApOB6jtSj1etX+jkMOvJwIDAQABo2MwYTAO
BgNVHQ8BAf8EBAMCAYYwDwYDVR0TAQH/BAUwAwEB/zAdBgNVHQ4EFgQUA95QNVbR
TLtm8KPiGxvDl7I90VUwHwYDVR0jBBgwFoAUA95QNVbRTLtm8KPiGxvDl7I90VUw
DQYJKoZIhvcNAQEFBQADggEBAMucN6pIExIK+t1EnE9SsPTfrgT1eXkIoyQY/Esr
hMAtudXH/vTBH1jLuG2cenTnmCmrEbXjcKChzUyImZOMkXDiqw8cvpOp/2PV5Adg
06O/nVsJ8dWO41P0jmP6P6fbtGbfYmbW0W5BjfIttep3Sp+dWOIrWcBAI+0tKIJF
PnlUkiaY4IBIqDfv8NZ5YBberOgOzW6sRBc4L0na4UU+Krk2U886UAb3LujEV0ls
YSEY1QSteDwsOoBrp+uvFRTp2InBuThs4pFsiv9kuXclVzDAGySj4dzp30d8tbQk
CAUw7C29C79Fv1C5qfPrmAESrciIxpg0X40KPMbp1ZWVbd4=
-----END CERTIFICATE-----
)rawliteral";

char clientId[32], subTopic[64];

NetworkClientSecure secureClient;
PubSubClient        mqttClient(secureClient);

volatile bool isConnected = false;

// WiFi 事件回调函数
void onWiFiEvent(WiFiEvent_t event) {
    switch (event) {
        case ARDUINO_EVENT_WIFI_STA_GOT_IP:
            LOG_I(TAG, "WiFi 已就绪，IP 地址: %s", WiFi.localIP().toString().c_str());
            isConnected = true;
            break;
        case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
            LOG_W(TAG, "WiFi 断开连接");
            isConnected = false;
            break;
        default:
            break;
    }
}

// MQTT 连接
void connectMQTT() {
    if (!isConnected) return; // 没网络就不尝试

​    LOG_I(TAG, "正在发起 TLS 握手并连接 MQTT...");
​    if (mqttClient.connect(clientId)) {
​        LOG_I(TAG, "MQTT 已连接");
​        mqttClient.subscribe(subTopic, 1);
​    } else {
​        LOG_E(TAG, "连接失败, 状态码=%d", mqttClient.state());
​    }
}

// MQTT 消息回调
void onMessageReceived(char* topic, byte* payload, unsigned int length) {
    String msg = String((char*)payload).substring(0, length);
    LOG_I(TAG, "加密通道收到 [%s]: %s", topic, msg.c_str());
}

void setup() {
    Serial.begin(115200);
    // 配置WiFi
    WiFi.onEvent(onWiFiEvent);
    WiFi.mode(WIFI_STA);
    WiFi.setAutoReconnect(true);
    WiFi.begin(ssid, password);
    // 生成设备 ID 和主题
    uint8_t mac[6];
    WiFi.macAddress(mac);
    snprintf(clientId, sizeof(clientId), "esp32_%02X%02X%02X", mac[3], mac[4], mac[5]);
    snprintf(subTopic, sizeof(subTopic), "esp32/%02X%02X%02X/control", mac[3], mac[4], mac[5]);
    LOG_I(TAG,"订阅主题：%s",subTopic);

​    // 配置安全客户端
​    // 加载证书以验证服务器身份（生产环境必须）
​    secureClient.setCACert(rootCACert);
​    
​    // 如果证书过期或仅用于测试，可使用此函数跳过校验（不推荐）
​    // secureClient.setInsecure();

​    //  配置 MQTT
​    mqttClient.setServer(mqttBroker, mqttPort);
​    mqttClient.setCallback(onMessageReceived);
​    mqttClient.setBufferSize(1024); // TLS 数据包较大，建议调大缓存

​    LOG_I(TAG, "系统初始化完成，TLS 准备就绪...");
}

void loop() {
    mqttClient.loop();   // 保持 MQTT 心跳

​    unsigned long now = millis();
​    
​    // 如果连接掉线，每 5 秒尝试重连一次 (非阻塞)
​    if (!mqttClient.connected()) {
​        static unsigned long lastRetry = 0;
​        if (now - lastRetry > 10000  || lastRetry==0) {
​            lastRetry = now;
​            connectMQTT();
​        }
​    } 
}

/*
 * 示例程序 6-25：MQTT智能家居控制系统
 * 功能：多主题发布订阅、JSON指令解析、执行反馈、遗嘱消息
 */
 #include <WiFi.h>
 #include <PubSubClient.h>
 #include <ArduinoJson.h>
 #include "log_config.h"

#define TAG       "MQTT_HOME"
#define LED_PIN   2
#define RELAY_PIN 4

const char* ssid       = "Wokwi-GUEST";
const char* password   = "";
const char* mqttBroker = "broker.emqx.io";
const int   mqttPort   = 1883;

// 全局变量
char clientId[32], TOPIC_DATA[64], TOPIC_CONTROL[64], TOPIC_RESPONSE[64], TOPIC_STATUS[64];
volatile bool isConnected = false; 
unsigned long lastPublishTime = 0;
const long    publishInterval = 15000; 

NetworkClient   networkClient;
PubSubClient    mqttClient(networkClient);

// 反馈执行结果 (JSON)
void publishResponse(const char* command, int value, const char* result) {
    JsonDocument doc;
    doc["command"] = command;
    doc["value"]   = value;
    doc["result"]  = result;
    
    char payload[128];
    serializeJson(doc, payload);
    mqttClient.publish(TOPIC_RESPONSE, payload);
    LOG_I(TAG, "反馈已发布: %s", payload);
}

//  执行逻辑
void executeCommand(const char* command, int value) {
    int targetPin = -1;
    if (strcmp(command, "led") == 0) targetPin = LED_PIN;
    else if (strcmp(command, "relay") == 0) targetPin = RELAY_PIN;

​    if (targetPin == -1) {
​        publishResponse(command, value, "unknown_command");
​        return;
​    }
​    if (value != 0 && value != 1) {
​        publishResponse(command, value, "invalid_value");
​        return;
​    }
​    digitalWrite(targetPin, value);
​    LOG_I(TAG, "%s -> %d", command, value);
​    publishResponse(command, value, "success");
}

//  MQTT 消息回调
void onMessageReceived(char* topic, byte* payload, unsigned int length) {
    LOG_I(TAG, "收到主题 [%s] 的消息", topic);
    
    JsonDocument doc;
    DeserializationError err = deserializeJson(doc, payload, length);
    if (err) {
        LOG_E(TAG, "JSON 解析失败: %s", err.c_str());
        return;
    }

​    const char* command = doc["command"] | "unknown";
​    int value = doc["value"] | -1;
​    executeCommand(command, value);
}

// 发布传感器数据 
void publishSensorData() {
    JsonDocument doc;
    doc["temp"]   = 20.0 + random(0, 100) / 10.0;
    doc["humi"]   = random(40, 81);
    doc["led"]    = digitalRead(LED_PIN);
    doc["relay"]  = digitalRead(RELAY_PIN);

​    char payload[200];
​    serializeJson(doc, payload);
​    mqttClient.publish(TOPIC_DATA, payload);
​    LOG_I(TAG, "数据上报: %s", payload);
}

//  MQTT 连接 (非阻塞) 
void connectMQTT() {
    if (!isConnected) return;

​    LOG_I(TAG, "尝试连接 MQTT...");
​    bool ok = mqttClient.connect(clientId, nullptr, nullptr, TOPIC_STATUS, 1, true, "offline");

​    if (ok) {
​        LOG_I(TAG, "MQTT 已连接");
​        mqttClient.publish(TOPIC_STATUS, "online", true); // 发布在线保留消息
​        mqttClient.subscribe(TOPIC_CONTROL, 1);
​        mqttClient.subscribe(TOPIC_STATUS, 1);
​    } else {
​        LOG_E(TAG, "连接失败, state=%d", mqttClient.state());
​    }
}

//  WiFi 事件回调
void onWiFiEvent(WiFiEvent_t event) {
    switch (event) {
        case ARDUINO_EVENT_WIFI_STA_GOT_IP:
            LOG_I(TAG, "WiFi 已连接，IP: %s", WiFi.localIP().toString().c_str());
            isConnected = true;
            break;
        case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
            LOG_W(TAG, "WiFi 断开");
            isConnected = false;
            break;
        default:
            break;
    }
}

void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    pinMode(RELAY_PIN, OUTPUT);

​    // 1. WiFi 配置
​    WiFi.onEvent(onWiFiEvent);
​    WiFi.mode(WIFI_STA);
​    WiFi.setAutoReconnect(true);
​    WiFi.begin(ssid, password);

​    // 2. 生成主题 (基于 MAC 地址)
​    uint8_t mac[6];
​    WiFi.macAddress(mac);
​    snprintf(clientId, sizeof(clientId), "esp32_%02X%02X%02X", mac[3], mac[4], mac[5]);
​    snprintf(TOPIC_DATA, 64, "home/%s/data", clientId);
​    snprintf(TOPIC_CONTROL, 64, "home/%s/control", clientId);
​    snprintf(TOPIC_RESPONSE, 64, "home/%s/response", clientId);
​    snprintf(TOPIC_STATUS, 64, "home/%s/status", clientId);
​    LOG_I(TAG, "主题已生成：data=%s", TOPIC_DATA);
​    
​    // 3. MQTT 配置
​    mqttClient.setServer(mqttBroker, mqttPort);
​    mqttClient.setCallback(onMessageReceived);
​    mqttClient.setBufferSize(512);
​    mqttClient.setKeepAlive(30);
​    
​    LOG_I(TAG, "智能家居节点初始化完成");
}

void loop() {
    mqttClient.loop();

​    unsigned long now = millis();

​    // 1. 处理重连 (非阻塞)
​    if (isConnected && !mqttClient.connected()) {
​        static unsigned long lastRetry = 0;
​        if (now - lastRetry > 5000) {
​            lastRetry = now;
​            connectMQTT();
​        }
​    }

​    // 2. 定时上报数据
​    if (mqttClient.connected() && (now - lastPublishTime >= publishInterval)) {
​        lastPublishTime = now;
​        publishSensorData();
​    }
}