#ifndef DUMMY_SENTIMENT_HPP
#define DUMMY_SENTIMENT_HPP

#include <string>

#include "../Engine/Executer.hpp"
#include "../Logger/AsyncLogger.hpp"
#include "./Sentiment.hpp"

class DummySentiment : public Sentiment {
 public:
  DummySentiment(string r) { req = r; }
  Response getSentiment() {
      return Response{"(dummy) POSITIVE", 1.0};
  }
};

#endif  // !DUMMY_SENTIMENT_HPP
