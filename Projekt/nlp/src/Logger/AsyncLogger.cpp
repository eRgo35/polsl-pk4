#include "../../include/Logger/AsyncLogger.hpp"

AsyncLogger* AsyncLogger::pinstance_{nullptr};
std::mutex AsyncLogger::mutex_;

AsyncLogger* AsyncLogger::GetInstance(const std::string& path) {
  std::lock_guard<std::mutex> lock(mutex_);
  if (pinstance_ == nullptr) pinstance_ = new AsyncLogger(path);
  return pinstance_;
}
