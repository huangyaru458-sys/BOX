# ESP32 分模块验证说明

每个功能单独放一个独立目录，便于在 Arduino IDE 中逐个烧录验证。

## 当前已建立的模块
- `01_fan_l298n_test`：L298N 风扇通断验证
- `02_dht11_test`：DHT11 温湿度验证
- `03_hcsr04_test`：HC-SR04 超声波测距验证
- `04_hcsr501_test`：HC-SR501 人体红外验证
- `05_mq135_test`：MQ-135 空气质量验证
- `06_mpu6050_test`：MPU6050 姿态验证
- `07_keypad_oled_buzzer_test`：4×4 键盘 + 1.3 寸 OLED + 蜂鸣器验证

## 推荐验证顺序
1. 风扇 L298N 模块
2. DHT11 温湿度
3. HC-SR04 超声波
4. HC-SR501 人体红外
5. MQ-135 空气质量
6. MPU6050 姿态
7. OLED 显示
8. 矩阵键盘
9. 联网与 MQTT

## 统一接线基准
- DHT11 `DATA -> GPIO17`
- MQ-135 `AO -> GPIO34`
- HC-SR04 `Trig -> GPIO2`，`Echo -> GPIO4`
- HC-SR501 `OUT -> GPIO16`
- MPU6050 `SDA -> GPIO21`，`SCL -> GPIO22`
- OLED `SDA -> GPIO21`，`SCL -> GPIO22`
- 键盘 `R1=GPIO18`，`R2=GPIO19`，`R3=GPIO23`，`R4=GPIO32`，`C1=GPIO25`，`C2=GPIO26`，`C3=GPIO13`，`C4=GPIO33`
- 蜂鸣器 `GPIO5`
- LED `GPIO14`、`GPIO12`
- L298N `ENA -> GPIO27`，`IN1 -> GPIO15`，`IN2 -> GND`
- L298N 的 `ENA` 只需要接一个 ESP32 引脚；如果板子上有 `ENA` 跳帽，做 PWM 调速时通常要拔掉跳帽

## 新增测试模块

### 7. 4×4 键盘 + 1.3 寸 OLED + 蜂鸣器
- 适合先验证按键输入、屏幕显示、蜂鸣器联动
- OLED 推荐 I2C 接法：`SDA -> GPIO21`，`SCL -> GPIO22`
- 蜂鸣器 `IO -> GPIO5`
- 1.3 寸 OLED 常见为 `SH1106 128x64`
- 如果你的 OLED 实际驱动是 `SSD1306`，只需要替换代码里的显示器构造器
