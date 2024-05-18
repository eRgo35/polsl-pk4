#ifndef TRANSLATE_HPP
#define TRANSLATE_HPP

#include <string>

#include "../Engine/Language.hpp"

namespace MT {
class Translate {
 private:
  Language source;
  Language destination;

 public:
  Translate(Language source, Language destination)
      : source(source), destination(destination) {}

  virtual std::string translate(std::string text) const = 0;
};
}  // namespace MT

#endif  // !TRANSLATE_HPP
