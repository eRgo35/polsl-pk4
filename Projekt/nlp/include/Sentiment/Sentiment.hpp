#ifndef SENTIMENT_HPP
#define SENTIMENT_HPP

#include <iostream>

#include "./Stream.hpp"
#include "./Tokenizer.hpp"

class Sentiment {
  Stream rpc;
  Tokenizer wordList;
};

#endif  // !SENTIMENT_HPP
