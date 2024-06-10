#include "../../include/Engine/PythonBinding.hpp"

PythonBinding* PythonBinding::pinstance_{nullptr};
std::mutex PythonBinding::mutex_;

PythonBinding* PythonBinding::GetInstance() {
  std::lock_guard<std::mutex> lock(mutex_);
  if (pinstance_ == nullptr) pinstance_ = new PythonBinding();
  return pinstance_;
}
