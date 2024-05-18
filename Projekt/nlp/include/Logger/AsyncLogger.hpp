#ifndef ASYNC_LOGGER_HPP
#define ASYNC_LOGGER_HPP

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string>

#include "../Engine/Color.hpp"

class AsyncLogger {
 private:
  static AsyncLogger* pinstance_;
  static std::mutex mutex_;

  std::string line_former(std::string message) {
    std::stringstream line;
    std::time_t time = std::time(nullptr);
    line << std::put_time(std::localtime(&time), "%F %T") << " | " << message;
    return line.str();
  }

 protected:
  AsyncLogger(const std::string path) : path_(path) {}
  ~AsyncLogger() {}
  std::string path_;

 public:
  AsyncLogger(AsyncLogger& other) = delete;
  void operator=(const AsyncLogger&) = delete;

  static AsyncLogger* GetInstance(const std::string& path);

  void log(std::string message) {
    std::cout << line_former(message) << std::endl;
  }

  void warn(std::string message) {
    Color* color = Color::Load();
    std::cout << color->get("yellow") << line_former(message)
              << color->get("reset") << std::endl;
  }

  void error(std::string message) {
    Color* color = Color::Load();
    std::cout << color->get("red") << line_former(message)
              << color->get("reset") << std::endl;
  }
};

#endif  // !ASYNC_LOGGER_HPP
