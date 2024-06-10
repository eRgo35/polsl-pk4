#ifndef PIPELINE_HPP
#define PIPELINE_HPP

#include <boost/python.hpp>
#include <string>

#include "../Logger/AsyncLogger.hpp"
#include "./Sentiment.hpp"

namespace py = boost::python;
using namespace std;

class Pipeline : public Sentiment {
 public:
  Pipeline(string r) { req = r; }
  Response getSentiment() {
    AsyncLogger *console = AsyncLogger::GetInstance();

    std::stringstream cmd;
    cmd << "python models/sentiment/sentiment_film_review_pipeline.py \"" << req
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
    // try {
    //     py::object main_module = py::import("__main__");
    //     py::object main_namespace = main_module.attr("__dict__");

    //     py::exec_file("models/sentiment/sentiment_film_review_pipeline.py",
    //     main_namespace);

    //     py::object resString = py::eval(string("analyze("+req+")").c_str(),
    //     main_namespace);

    //     std::string responseString = py::extract<std::string>(resString[0]);
    //     float responseFloat = py::extract<float>(resString[1]);
    //     return Response{responseString, responseFloat};
    // } catch (py::error_already_set const &) {
    //     PyErr_Print();
    //     return Response{"Error", 0};
    // }
  }
};

#endif