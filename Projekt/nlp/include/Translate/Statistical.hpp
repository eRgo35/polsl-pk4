#ifndef STATISTICAL_TRANSLATE_HPP
#define STATISTICAL_TRANSLATE_HPP

#include <string>
#include <cctype>
#include <iostream>
#include <sstream>
#include <unordered_map>

// #include "../Engine/Trainer.hpp"
// #include "./Translate.hpp"

#include "../Engine/Language.hpp"
#include "./Translate.hpp"
#include "../Engine/Executer.hpp"
#include "../Logger/AsyncLogger.hpp"

// comms.listen();
// dummycomms.listen();

// logger->log("Hello Log Message!");
// logger->warn("This is a warning!");
// logger->log("Hello Log Message!");
// logger->error("Error occured message color!");

// Language src("en");
// Language des("pl");

// MT::DummyTranslate engine(src, des);
// logger->log(engine.translate("Hello, dummy translate!"));

// logger->error("---------------------------");
// logger->error("Training statistical model:");

// MT::Trainer model("stat_model_v1.smt");

// std::string consume_path = "/home/mike/Projects/debug/sources.txt";
// std::string consume_pl_path = "/home/mike/Projects/debug/targets.txt";

// logger->log("Consume path: " + consume_path);
// logger->log("Consume path: " + consume_pl_path);

// model.consume(consume_path, consume_pl_path);

// // std::string save_path =
// "/home/mike/Projects/nlp-platform/nlp/stat_model_v1.smt";
// // logger->log("Model path: " + save_path);
// // model.save(save_path);

// MT::StatisticalTranslate stats(src, des);
// stats.use(model, model);
// logger->log(stats.translate("I just want to tell you how I am feeling"));

namespace MT {
  class StatisticalTranslate : public Translate {
    public:
      StatisticalTranslate(Language source, Language destination)
          : Translate(source, destination) {} 

      std::string translate(std::string text) const override {
        AsyncLogger *console = AsyncLogger::GetInstance();
        
        std::string response = "(smt) This is translated I swear";

        if (source != "en" && destination != "pl") {
          return response;
        }

        std::stringstream cmd;
        cmd << "python models/translation/smt.py \""
            << text << "\" 2> /dev/null";

        response = Executor::exec(cmd.str().c_str());
        console->log(response);

        return response;
      }
  };
// class StatisticalTranslate : public Translate {
//  private:
//   Trainer* src;
//   Trainer* dst;

//   bool is_ready = false;

//  public:
//   StatisticalTranslate(Language source, Language destination)
//       : Translate(source, destination) {}

//   bool use(Trainer model_src, Trainer model_dst) {
//     src = &model_src;
//     dst = &model_dst;

//     is_ready = true;

//     return true;
//   }

//   std::string translate(std::string text) const override {
//     std::string response = "Model uninitialized!";

//     if (!is_ready) return response;

//     std::stringstream translation;

//     std::vector<std::string> words;
//     std::stringstream ss(text);

//     std::string wordt;

//     while (ss >> wordt) {
//       std::string clean;
//       for (char c : wordt)
//         if (std::isalpha(c)) clean += std::tolower(c);

//       words.push_back(clean);
//     }

//     std::unordered_map<std::string, std::string>* align_table =
//         src->get_align_table();

//     for (const auto& word : words) {
//       if (align_table->find(word) != align_table->end())
//         translation << align_table->at(word) << " ";
//       else
//         translation << "[unknown] ";
//     }

//     return translation.str();
//   }
// };
}  // namespace MT

#endif  // !STATISTICAL_TRANSLATE_HPP
