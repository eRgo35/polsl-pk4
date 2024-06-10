#ifndef MT5_TRANSLATE_HPP
#define MT5_TRANSLATE_HPP

#include <string>
#include <sstream>

#include "../Engine/Language.hpp"
#include "./Translate.hpp"
#include "../Engine/Executer.hpp"
#include "../Logger/AsyncLogger.hpp"

namespace MT {
class MT5Translate : public Translate {
 public:
  MT5Translate(Language source, Language destination)
      : Translate(source, destination) {}

  std::string translate(std::string text) const override {
    AsyncLogger *console = AsyncLogger::GetInstance();

    std::string response = "(mt5) This is translated I swear";
    std::string model = "sdadas/mt5-base-translator-en-pl";

    if (source == "en" && destination == "pl") {
      model = "sdadas/mt5-base-translator-en-pl";
    }
    else if (source == "pl" && destination == "en") {
      model = "sdadas/mt5-base-translator-pl-en";
    }
    else {
      model = "sdadas/mt5-base-translator-en-pl";
    }

    std::stringstream cmd;
    cmd << "python models/translation/mt5.py \""
        << source << "\" \""
        << destination << "\" \""
        << model << "\" \""
        << text << "\" 2> /dev/null";

    response = Executor::exec(cmd.str().c_str());
    console->log(response);

    return response;
  }
};
}  // namespace MT

#endif  // !MT5_TRANSLATE_HPP
