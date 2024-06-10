#ifndef TRANSLATOR_HPP
#define TRANSLATOR_HPP

#include <boost/python.hpp>
#include <string>

#include "../Engine/Language.hpp"
#include "../Logger/AsyncLogger.hpp"
#include "../Translate/Dummy.hpp"

namespace py = boost::python;

namespace MT {
class Translator {
 private:
  std::string request = "Invalid request";

 public:
  Translator(std::string request) : request(request) {}

  std::string process_request() {
    // Py_Initialize();

    // try {
    //   py::object main_module = py::import("__main__");
    //   py::object main_namespace = main_module.attr("__dict__");

    //   py::exec_file("models/translation/mt5.py", main_namespace);

    //   py::object mt5_translate = main_namespace["mt5_translate"];
    //   py::object result = mt5_translate(request);

    //   std::string response = py::extract<std::string>(result);

    //   // Language pl("pl");
    //   // Language en("en");
    //   // MT::DummyTranslate dummyTranslate(en, pl);

    //   // response = dummyTranslate.translate("Hello world!");

    //   return response;
    // } catch (py::error_already_set const &) {
    //   PyErr_Print();
    //   return "An error occurred while translating";
    // }
  return "aaaa";
  }
};
}  // namespace MT

#endif  // !TRANSLATOR_HPP