#ifndef COLOR_HPP
#define COLOR_HPP

#include <algorithm>
#include <mutex>
#include <string>
#include <unordered_map>

class Color {
 private:
  static Color *pinstance_;
  static std::mutex mutex_;

 protected:
  Color() {}
  ~Color() {}

  std::unordered_map<std::string, std::string> colors = {
      {"RESET", "\033[0m"},    {"BLACK", "\033[30m"},  {"RED", "\033[31m"},
      {"GREEN", "\033[32m"},   {"YELLOW", "\033[33m"}, {"BLUE", "\033[34m"},
      {"MAGENTA", "\033[35m"}, {"CYAN", "\033[36m"},   {"WHITE", "\033[37m"}};

 public:
  Color(Color &other) = delete;

  void operator=(const Color &) = delete;

  static Color *Load();

  std::string get(std::string color) {
    std::transform(color.begin(), color.end(), color.begin(), ::toupper);
    return colors.at(color);
  }

  void add(std::string color_name, std::string color_code) {
    colors.at(color_name) = color_code;
  }
};

#endif  // !COLOR_HPP
