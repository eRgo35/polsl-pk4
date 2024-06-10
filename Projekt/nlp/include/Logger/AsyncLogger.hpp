#ifndef ASYNC_LOGGER_HPP
#define ASYNC_LOGGER_HPP

#include <chrono>
#include <ctime>
#include <fstream>
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

  template <typename... Args>
  std::string concatenate_messages(Args... args) {
    std::ostringstream oss;
    (oss << ... << args);
    return oss.str();
  }

 protected:
  std::ofstream log_file;
  AsyncLogger() {
    log_file.open("latest.log", std::ios::app);
    if (!log_file.is_open()) {
      std::cerr << "Error opening log file." << std::endl;
    }
  }

  ~AsyncLogger() { log_file.close(); }

 public:
  AsyncLogger(AsyncLogger& other) = delete;
  void operator=(const AsyncLogger&) = delete;

  static AsyncLogger* GetInstance();

  template<typename... Args>
  void log(Args... args) {
    std::string message = concatenate_messages(args...);
    std::string line_entry = line_former(message);
    std::cout << line_entry << std::endl;

    if (log_file.is_open()) {
      log_file << line_entry << std::endl;
      log_file.flush();
    }
  }

  template<typename... Args>
  void warn(Args... args) {
    std::string message = concatenate_messages(args...);
    Color* color = Color::Load();
    std::string line_entry = line_former(message);

    std::cout << color->get("yellow") << line_entry << color->get("reset")
              << std::endl;

    if (log_file.is_open()) {
      log_file << line_entry << std::endl;
      log_file.flush();
    }
  }

  template<typename... Args>
  void error(Args... args) {
    std::string message = concatenate_messages(args...);
    Color* color = Color::Load();
    std::string line_entry = line_former(message);

    std::cout << color->get("red") << line_entry << color->get("reset")
              << std::endl;

    if (log_file.is_open()) {
      log_file << line_entry << std::endl;
      log_file.flush();
    }
  }
};

#endif  // !ASYNC_LOGGER_HPP
