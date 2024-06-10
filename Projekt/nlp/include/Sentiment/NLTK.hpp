#ifndef NLTK_HPP
#define NLTK_HPP

// #include <boost/python.hpp>
#include <list>
#include <string>

// #include "../Engine/PythonBinding.hpp"
#include "../Engine/Executer.hpp"
#include "../Logger/AsyncLogger.hpp"
#include "./Sentiment.hpp"

namespace py = boost::python;
// using namespace std;

class NLTK : public Sentiment {
 public:
  NLTK(string r) { req = r; }
  Response getSentiment() {
    AsyncLogger *console = AsyncLogger::GetInstance();

    std::stringstream cmd;
    cmd << "python models/sentiment/sentiment_amazon_review_nltk.py \"" << req
        << "\" 2> /dev/null";
    std::string response = Executor::exec(cmd.str().c_str());
    console->log(response);

    std::string::size_type pos = response.find('\07');
    if (pos != std::string::npos) {
      return Response{response.substr(0, pos),
                      std::stof(response.substr(pos + 1))};
    } else {
      return Response{"Error", 0};
    }

    // return Response{"Error", 0};

    // PythonBinding* pyBinding = PythonBinding::GetInstance();
    // py::object* main_namespace = pyBinding->get_main_namespace();

    // py::object pyStringList = py::eval("stringlist()", *main_namespace);

    // console->log("Length of list", py::len(pyStringList));

    // for (int i = 0; i < py::len(pyStringList); i++) {
    //   std::string value = py::extract<std::string>(pyStringList[i]);
    //   console->log(i, "\t", value);
    // }

    // py::object analyze = main_namespace["call_python"];
    // py::object result = analyze("analyze_nltk", req);

    // std::string response = py::extract<std::string>(result);
    // std::string::size_type pos = response.find('\07');
    // if (pos != std::string::npos) {
    //   return Response{response.substr(0, pos),
    //                   std::stof(response.substr(pos + 1))};
    // } else {
    //   return Response{"Error", 0};
    // }

    // PythonBinding *pythonBinding = PythonBinding::GetInstance();
    // PyThreadState *global = pythonBinding->get_main();
    // PyGILState_STATE gstate = PyGILState_Ensure();
    // PyThreadState *nltkState = Py_NewInterpreter();
    // //   Py_Initialize();
    // if (nltkState == NULL) {
    //   PyErr_Print();
    //   PyGILState_Release(gstate);

    //   return Response{"Error", 0};
    // }
    // PyThreadState_Swap(nltkState);
    // try {
    //   py::object main_module = py::import("__main__");
    //   py::object main_namespace = main_module.attr("__dict__");

    //   py::exec_file("models/sentiment/sentiment_amazon_review_nltk.py",
    //                 main_namespace);

    //   //   py::object main_namespace = pythonBinding->get_main_namespace();

    //   py::object analyze = main_namespace["analyze"];
    //   py::object result = analyze(req);

    //   std::string response = py::extract<std::string>(result);
    //   Py_EndInterpreter(nltkState);
    //   PyThreadState_Swap(global);
    //   PyGILState_Release(gstate);
    //   std::string::size_type pos = response.find('\07');
    //   if (pos != std::string::npos) {
    //     return Response{response.substr(0, pos),
    //                     std::stof(response.substr(pos + 1))};
    //   } else {
    //     return Response{"Error", 0};
    //   }

    // } catch (py::error_already_set const &) {
    //   PyErr_Print();
    //   Py_EndInterpreter(nltkState);
    //   PyThreadState_Swap(global);
    //   PyGILState_Release(gstate);
    //   return Response{"Error", 0};
    // }
    // return Response{"Error", 0};
  }
};

#endif  // !NLTK_HPP
