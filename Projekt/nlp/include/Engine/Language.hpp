#ifndef LANGUAGE_HPP
#define LANGUAGE_HPP

#include <string>

class Language {
 private:
  std::string code;

 public:
  Language(std::string code) : code(code) {}

  std::string getCode() { return code; }

  void setCode(std::string new_code) { code = new_code; }

  friend std::istream &operator>>(std::istream &is, Language language) {
    std::string code;
    is >> code;
    language.code = code;
    return is;
  }

  friend std::ostream &operator<<(std::ostream &os, Language language) {
    os << language.code;
    return os;
  }

  bool operator==(const Language &other) const { return code == other.code; }
  
  bool operator==(const std::string &other) const { return code == other; }
  
  bool operator!=(const Language &other) const { return code != other.code; }
  
  bool operator!=(const std::string &other) const { return code != other; }
};

#endif  // !LANGUAGE_HPP
