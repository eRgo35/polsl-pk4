#ifndef TRAINER_HPP
#define TRAINER_HPP

#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_map>

#include "../Logger/AsyncLogger.hpp"

namespace MT {
class Trainer {
 private:
  std::unordered_map<std::string, double> model;
  std::unordered_map<std::string, double> model2;
  std::string model_name;
  std::unordered_map<std::string, std::string> align_table;

  std::string process_word(const std::string& word) {
    std::string cleaned;
    for (char c : word)
      if (std::isalpha(c)) cleaned += std::tolower(c);

    return cleaned;
  }

  std::vector<std::string> tokenize(const std::string& text) {
    std::stringstream ss(text);
    std::string word;

    std::vector<std::string> tokens;
    while (ss >> word) tokens.push_back(process_word(word));

    return tokens;
  }

  void set_frequency(const std::vector<std::string>& words) {
    for (const auto& word : words) model[word]++;
  }

 public:
  Trainer(std::string model_name) : model_name(model_name) {}

  double get_frequency(std::string& word) { return model[word]; }

  std::unordered_map<std::string, std::string>* get_align_table() {
    return &align_table;
  }

  bool load(std::string model_path) {
    std::ifstream file(model_path);
    std::string line;

    if (!file.good()) return false;

    while (std::getline(file, line)) {
      std::stringstream ss(line);
      std::string word;
      double probability;

      ss >> word >> probability;

      model[word] = probability;
    }

    return true;
  }

  bool save(std::string model_path) {
    std::ofstream file(model_path);

    if (!file.good()) return false;

    for (auto& pair : model) {
      file << pair.first << " " << pair.second << std::endl;
    }

    return true;
  }

  bool consume(std::string file_path, std::string file_path2) {
    std::ifstream file(file_path);
    std::ifstream file2(file_path2);
    std::string line1, line2;

    if (!file.good()) return false;

    while (std::getline(file, line1) && std::getline(file2, line2)) {
      std::vector<std::string> words1 = tokenize(line1);
      std::vector<std::string> words2 = tokenize(line2);

      // set_frequency(words1);
      // set_frequency(words2);

      for (const auto& word : words1) model[word]++;

      for (const auto& word : words2) model2[word]++;

      for (size_t i = 0; i < std::min(words1.size(), words2.size()); ++i) {
        align_table[words1[i]] = words2[i];
      }
    }

    return true;
  }
};
}  // namespace MT

#endif  // !TRAINER_HPP
#define TRAINER_HPPTRAINER_HPP
