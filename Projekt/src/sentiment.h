#ifndef SENTIMENT_H
#define SENTIMENT_H
#include "rpc.h"
#include <iostream>


class Sentiment{
    Stream rpc;
    Tokenizer wordList;
};

class NLTK: public Sentiment{

};

class NaiveBayes: public Sentiment{

};

class Token{
    std::string word;
};

class Tokenizer{
    Token t;
};



#endif