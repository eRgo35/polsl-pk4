#ifndef DUMMY_TRANSLATE_HPP
#define DUMMY_TRANSLATE_HPP

#include <string>

#include "../Engine/Language.hpp"
#include "./Translate.hpp"

namespace MT {
class DummyTranslate : public Translate {
 public:
  DummyTranslate(Language source, Language destination)
      : Translate(source, destination) {}

  std::string translate(std::string text) const override {
    std::string response = "(dummy) This is translated I swear";

    return response;
  }
};
}  // namespace MT

#endif  // !DUMMY_TRANSLATE_HPP
#define DUMMY_TRANSLATE_HPPDUMMY_TRANSLATE_HPP
