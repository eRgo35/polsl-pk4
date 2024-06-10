#include <ranges>
#include <string>
#include <boost/python.hpp>

#include "../include/Communication/Zmq.hpp"
#include "../include/Engine/PythonBinding.hpp"
#include "../include/Logger/AsyncLogger.hpp"

namespace py = boost::python;

int main(int argc, char** argv) {
  AsyncLogger* console = AsyncLogger::GetInstance();

  console->log("NLP Platform");
  console->log("Version 1.0.0");
  console->log("Copyright(c) 2024 Michał Czyż, Dawid Głąb");
  console->log("All Rights Reserved");

  Address address("127.0.0.1");
  Port port(5555);
  COMMS::ZmqCommunication com(address, port);

  auto args = std::views::iota(1, argc) | std::views::transform([&](int i) {
                return std::string(argv[i]);
              });

  for (const auto& arg : args) {
    if (arg == "-v" || arg == "--verbose") {
      com.verbose();
    }

    if (arg == "--version") {
      return 0;
    }
  }

  // Py_Initialize();

  // py::object main_module = py::import("__main__");
  // py::object main_namespace = main_module.attr("__dict__");

  // py::exec_file("models/hello.py", main_namespace);

  // PythonBinding* pyBinding = PythonBinding::GetInstance();
  // py::object *main_namespace = pyBinding->get_main_namespace();

  // py::object pyStringList = py::eval("stringlist()", *main_namespace);

  // console->log("Length of list", py::len(pyStringList));

  // for (int i = 0; i < py::len(pyStringList); i++) {
  //   std::string value = py::extract<std::string>(pyStringList[i]);
  //   console->log(i, "\t", value);
  // }

  com.listen();

  return 0;
}
