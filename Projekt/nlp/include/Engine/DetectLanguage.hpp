#ifndef DETECT_LANGUAGE_HPP
#define DETECT_LANGUAGE_HPP

#include "../Engine/Executer.hpp"
#include "../Logger/AsyncLogger.hpp"

class DetectLanguage {
 private:
  std::string request = "Invalid request";

 public:
  static std::string detect(std::string request) {
    AsyncLogger *console = AsyncLogger::GetInstance();

    std::stringstream cmd;
    cmd << "python models/translation/detect.py \"" << request
        << "\" 2> /dev/null";
    std::string response = Executor::exec(cmd.str().c_str());
    console->log(response);

    return response;
  }
};

#endif  // !DETECT_LANGUAGE_HPP