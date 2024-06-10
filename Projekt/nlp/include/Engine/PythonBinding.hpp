#ifndef PYTHON_BINDING_HPP
#define PYTHON_BINDING_HPP

#include <boost/python.hpp>
#include <mutex>

#include "../Logger/AsyncLogger.hpp"

namespace py = boost::python;

class PythonBinding {
 private:
  static PythonBinding* pinstance_;
  static std::mutex mutex_;

  py::object main_module;
  py::object main_namespace;
  PyThreadState *main;

 protected:
  PythonBinding() {
    AsyncLogger* console = AsyncLogger::GetInstance();

    try {
      Py_Initialize();
      main_module = py::import("__main__");
      main_namespace = main_module.attr("__dict__");
      main = PyThreadState_Get();

      // py::exec_file("models/hello.py", main_namespace);

      
    } catch (const boost::python::error_already_set&) {
      PyErr_Print();
      PyErr_Clear();
      console->log("Error occurred during Python initialization");
    }
  }

 public:
  PythonBinding(PythonBinding& other) = delete;
  void operator=(const PythonBinding&) = delete;

  static PythonBinding* GetInstance();

  py::object* get_main_namespace() { return &main_namespace; }

  PyThreadState* get_main() {
    return main;
  }
};

#endif  // !PYTHON_BINDING_HPP