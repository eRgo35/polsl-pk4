#include "../../include/Logger/AsyncLogger.hpp"

AsyncLogger* AsyncLogger::pinstance_{nullptr};
std::mutex AsyncLogger::mutex_;

AsyncLogger* AsyncLogger::GetInstance() {
  std::lock_guard<std::mutex> lock(mutex_);
  if (pinstance_ == nullptr) pinstance_ = new AsyncLogger();
  return pinstance_;
}
