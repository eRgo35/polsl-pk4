#ifndef ANNONIMIZE_HPP
#define ANNONIMIZE_HPP 

#include "../Engine/Executer.hpp"
#include "../Logger/AsyncLogger.hpp"

class Anonymize {
 private:
  std::string request = "Invalid request";

 public:
  static std::string anonymize(std::string request) {
    AsyncLogger *console = AsyncLogger::GetInstance();

    std::stringstream cmd;
    cmd << "python models/anonymize.py \"" << request
        << "\" 2> /dev/null";
    std::string response = Executor::exec(cmd.str().c_str());
    console->log(response);

    return response;
  }
};
#endif  // !ANNONIMIZE_HPP