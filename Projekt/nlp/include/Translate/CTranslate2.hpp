#ifndef CT2_TRANSLATE_HPP
#define CT2_TRANSLATE_HPP

#include <string>
#include <sstream>

#include "../Engine/Language.hpp"
#include "./Translate.hpp"
#include "../Engine/Executer.hpp"
#include "../Logger/AsyncLogger.hpp"

namespace MT {
class CTranslate : public Translate {
 public:
  CTranslate(Language destination)
      : Translate(destination, destination) {}

  std::string translate(std::string text) const override {
    AsyncLogger *console = AsyncLogger::GetInstance();

    std::string response = "(ct2) This is translated I swear";

    std::stringstream cmd;
    cmd << "python models/translation/ct2.py \""
        << destination << "\" \""
        << text << "\" 2> /dev/null";

    response = Executor::exec(cmd.str().c_str());
    console->log(response);

    return response;
  }
};
}  // namespace MT

#endif  // !CT2_TRANSLATE_HPP
