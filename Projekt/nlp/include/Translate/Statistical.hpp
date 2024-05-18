#ifndef STATISTICAL_TRANSLATE_HPP
#define STATISTICAL_TRANSLATE_HPP

#include "./Translate.hpp"
#include "../Engine/Trainer.hpp"

#include <cctype>
#include <sstream>
#include <unordered_map>
#include <iostream>

namespace MT {
class StatisticalTranslate : public Translate {
private:
  Trainer* src;
  Trainer* dst;
  
  bool is_ready = false;

public:
  StatisticalTranslate(Language source, Language destination)
      : Translate(source, destination) {}
  
  bool use(Trainer model_src, Trainer model_dst) {
    src = &model_src;
    dst = &model_dst;
    
    is_ready = true;

    return true;
  }
  
  std::string translate(std::string text) const override {
    std::string response = "Model uninitialized!";
    
    if (!is_ready)
      return response;
    
    std::stringstream translation;

    std::vector<std::string> words;
    std::stringstream ss(text);

    std::string wordt;

    while (ss >> wordt)
    {
      std::string clean;
      for (char c : wordt)
        if (std::isalpha(c))
          clean += std::tolower(c);

      words.push_back(clean);
    }

    std::unordered_map<std::string, std::string> *align_table = src->get_align_table();
    
    for (const auto& word : words) {
      if (align_table->find(word) != align_table->end())
        translation << align_table->at(word) << " ";
      else
        translation << "[unknown] ";
    }
    
    return translation.str();
  }
};
}  // namespace MT

#endif  // !STATISTICAL_TRANSLATE_HPP
#define STATISTICAL_TRANSLATE_HPPSTATISTICAL_TRANSLATE_HPP
