#include "../../include/Engine/Color.hpp"

#include <mutex>

Color* Color::pinstance_{nullptr};
std::mutex Color::mutex_;

Color* Color::Load() {
  std::lock_guard<std::mutex> lock(mutex_);
  if (pinstance_ == nullptr) pinstance_ = new Color();
  return pinstance_;
}
