/*
 * 示例程序 2-2：分级日志宏定义
 * 功能：分级日志宏定义，支持ERROR/WARN/INFO/DEBUG/VERBOSE五个等级
 * 建议将此段代码放置在项目头文件（log_config.h）中
 */
 
// 日志等级定义（数值越大，等级越高，输出信息越少）
#define LOG_LEVEL_VERBOSE  0
#define LOG_LEVEL_DEBUG    1
#define LOG_LEVEL_INFO     2
#define LOG_LEVEL_WARN     3
#define LOG_LEVEL_ERROR    4
#define LOG_LEVEL_NONE     5  // 关闭所有日志输出
 
// 设置当前日志等级
// 开发调试阶段：使用 LOG_LEVEL_DEBUG 或 LOG_LEVEL_VERBOSE
// 功能验证阶段：使用 LOG_LEVEL_INFO
// 发布部署阶段：使用 LOG_LEVEL_WARN 或 LOG_LEVEL_NONE
#define CURRENT_LOG_LEVEL  LOG_LEVEL_DEBUG
 
// 日志宏定义
// 使用 ##__VA_ARGS__ 支持可变参数（类似printf的格式化输出）
#if CURRENT_LOG_LEVEL <= LOG_LEVEL_ERROR
  #define LOG_E(tag, fmt, ...) \
      Serial.printf("[%10lu][ERROR][%s] " fmt "\n", (unsigned long)millis(), tag, ##__VA_ARGS__)
#else
  #define LOG_E(tag, fmt, ...)
#endif
 
#if CURRENT_LOG_LEVEL <= LOG_LEVEL_WARN
  #define LOG_W(tag, fmt, ...) \
      Serial.printf("[%10lu][WARN ][%s] " fmt "\n", (unsigned long)millis(), tag, ##__VA_ARGS__)
#else
  #define LOG_W(tag, fmt, ...)
#endif
 
#if CURRENT_LOG_LEVEL <= LOG_LEVEL_INFO
  #define LOG_I(tag, fmt, ...) \
      Serial.printf("[%10lu][INFO ][%s] " fmt "\n", (unsigned long)millis(), tag, ##__VA_ARGS__)
#else
  #define LOG_I(tag, fmt, ...)
#endif
 
#if CURRENT_LOG_LEVEL <= LOG_LEVEL_DEBUG
  #define LOG_D(tag, fmt, ...) \
      Serial.printf("[%10lu][DEBUG][%s] " fmt "\n", (unsigned long)millis(), tag, ##__VA_ARGS__)
#else
  #define LOG_D(tag, fmt, ...)
#endif
 
#if CURRENT_LOG_LEVEL <= LOG_LEVEL_VERBOSE
  #define LOG_V(tag, fmt, ...) \
      Serial.printf("[%10lu][VERB ][%s] " fmt "\n", (unsigned long)millis(), tag, ##__VA_ARGS__)
#else
  #define LOG_V(tag, fmt, ...)
#endif