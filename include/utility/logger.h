/**
 * @file logger.h
 * @author yanqing (yanqing.cao@huaxinjushu.com)
 * @brief
 * @version 0.1
 * @date 2023-03-29
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <fmt/format.h>
#include <iostream>
#include <string>
#include <time.h>
namespace utl {
#define FOREACH_TOOL(X) X(UNKW)

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

enum ToolId { FOREACH_TOOL(GENERATE_ENUM) SIZE };
class Logger {
public:
  static void Init_log() {
    time_t t = time(nullptr);
    struct tm ltm, ltm2;
    localtime_r(&t, &ltm);
    gmtime_r(&t, &ltm2);
    time_t t1 = mktime(&ltm);
    time_t t2 = mktime(&ltm2);
    time_diff_ = static_cast<long>(t1) - static_cast<long>(t2);
  }

private:
  template <typename... Args>
  static void log(ToolId tool, int level, const std::string &message,
                  const Args &...args) {
    time_t t_cur = time(nullptr) + time_diff_;
    struct tm tm_cur;
    gmtime_r(&t_cur, &tm_cur);
    struct tm *tmp = &tm_cur;

    fmt::print(fmt::print("[{} {}-{:04d}/{:02d}/{:02d}-{:02d}:{:02d}:{:02d}] " +
                              message + "\n",
                          utl_level_names_[level], utl_tool_names_[tool],
                          tmp->tm_year + 1900, tmp->tm_mon + 1, tmp->tm_mday,
                          tmp->tm_hour, tmp->tm_min, tmp->tm_sec, args...);)
  }

  static constexpr const char *utl_tool_names_[] = {
      FOREACH_TOOL(GENERATE_STRING)};
  static constexpr const char *utl_level_names_[] = {
      "TRACE", "DEBUG", "INFO ", "WARN ", "ERROR", "CRIT ", "OFF  "};
  static long int time_diff_;
};

} // namespace utl
