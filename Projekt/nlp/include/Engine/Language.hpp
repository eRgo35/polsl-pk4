#ifndef LANGUAGE_HPP
#define LANGUAGE_HPP

#include <string>

class Language {
 private:
  std::string code;

 public:
  Language(std::string code) : code(code) {}
};

#endif  // !LANGUAGE_HPP
