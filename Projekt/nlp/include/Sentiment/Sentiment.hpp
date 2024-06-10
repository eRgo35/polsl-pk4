#ifndef SENTIMENT_HPP
#define SENTIMENT_HPP

#include <boost/python.hpp>
#include <string>

namespace py = boost::python;
using namespace std;

struct Response{
  string decision;
  float score;
};

class Sentiment {
  public:
    string req;
    string mode;
    virtual Response getSentiment() = 0;
};

#endif  // !SENTIMENT_HPP
