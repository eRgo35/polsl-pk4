#ifndef OPUS_TRANSLATE_HPP
#define OPUS_TRANSLATE_HPP

#include <string>
#include <sstream>

#include "../Engine/Language.hpp"
#include "./Translate.hpp"
#include "../Engine/Executer.hpp"
#include "../Logger/AsyncLogger.hpp"


namespace MT {
class OpusTranslate : public Translate {
 public:
  OpusTranslate(Language source, Language destination)
      : Translate(source, destination) {}

  std::string translate(std::string text) const override {
    AsyncLogger *console = AsyncLogger::GetInstance();

    std::string response = "(opus) This is translated I swear";
    std::string model = "jproboszcz/opus-mt-en-pl";

    if (source == "en" && destination == "pl") {
      model = "jproboszcz/opus-mt-en-pl";
    }
    else if (source == "pl" && destination == "en") {
      model = "Helsinki-NLP/opus-mt-pl-en";
    }
    else {
      model = "jproboszcz/opus-mt-en-pl";
    }
    
    std::stringstream cmd;
    cmd << "python models/translation/opus.py \""
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

#endif  // !OPUS_TRANSLATE_HPP
