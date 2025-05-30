#ifndef EXECUTER_HPP
#define EXECUTER_HPP

#include <cstdlib>
#include <string>
#include <memory>

class Executor {
 public:
  Executor() {}
  ~Executor() {}

  static std::string exec(const char *cmd) {
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) return "ERROR";
    char buffer[128];
    std::string result = "";
    while (!feof(pipe.get())) {
      if (fgets(buffer, 128, pipe.get()) != NULL) result += buffer;
    }
    return result;
  }
};

#endif  // !EXECUTER_HPP