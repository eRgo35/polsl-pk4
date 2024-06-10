#ifndef ZMQ_COMMUNICATION_HPP
#define ZMQ_COMMUNICATION_HPP

#include <chrono>
#include <iomanip>
#include <iostream>
#include <ranges>
#include <sstream>
#include <string>
#include <string_view>
#include <thread>
#include <vector>
// #include <Python.h>
#include <boost/python.hpp>
#include <concepts>

#include "../Engine/Annonimize.hpp"
#include "../Engine/DetectLanguage.hpp"
#include "../Engine/Translator.hpp"
#include "../Logger/AsyncLogger.hpp"
#include "../Sentiment/NLTK.hpp"
#include "../Sentiment/Pipeline.hpp"
#include "../Sentiment/DummySentiment.hpp"
#include "../Translate/CTranslate2.hpp"
#include "../Translate/Dummy.hpp"
#include "../Translate/MT5.hpp"
#include "../Translate/Opus.hpp"
#include "../Translate/Statistical.hpp"
#include "./Communication.hpp"
#include "./rpc.hpp"
#include "./rpcWorker.hpp"

namespace py = boost::python;
template <class T>
concept StringLike = std::is_convertible_v<T, std::string_view>;

template <class U>
concept FloatLike = std::floating_point<U>;

template <StringLike X>
string checkValidityString(X data) {
  return data;
};
template <FloatLike Y>
float checkValidityFloat(Y data) {
  return data;
};
void start_broker(int &verbose, Address &address, Port &port) {
  AsyncLogger *console = AsyncLogger::GetInstance();

  s_version_assert(4, 0);
  s_catch_signals();

  broker brk(verbose);

  std::stringstream uri;
  uri << "tcp://" << address << ":" << port;

  brk.bind(uri.str());
  brk.start_brokering();

  if (s_interrupted) {
    console->error("W: interrupt received, shutting down...");
  }
}

void ping_worker(int &verbose, Address &address, Port &port) {
  AsyncLogger *console = AsyncLogger::GetInstance();

  std::stringstream uri;
  uri << "tcp://" << address << ":" << port;

  mdwrk session(uri.str(), "ping", verbose);
  zmsg *reply = 0;

  while (true) {
    console->log("Reply out:");
    zmsg *request = session.recv(reply);
    if (request == 0) {
      break;  //  Worker was interrupted
    }
    reply = request;
  }

  free(reply);
}

void translate_worker(int &verbose, Address &address, Port &port) {
  AsyncLogger *console = AsyncLogger::GetInstance();

  std::stringstream uri;
  uri << "tcp://" << address << ":" << port;

  mdwrk session(uri.str(), "translate", verbose);
  zmsg *reply = 0;
  std::string response = "Invalid response";

  while (true) {
    console->warn("Translating works");
    zmsg *request = session.recv(reply);

    if (request == 0) {
      break;  //  Worker was interrupted
    }

    console->error(request->body());

    std::string req = std::string(request->body());
    char delim = '\07';

    std::stringstream ss(req);
    std::vector<std::string> parts;
    std::string part;

    while (getline(ss, part, delim)) {
      parts.push_back(part);
    }

    std::string srcLanguage = parts[0];
    std::string dstLanguage = parts[1];
    std::string mode = parts[2];
    std::string data = parts[3];

    console->warn(srcLanguage, ", ", dstLanguage, ", ", mode, ", ", data);

    Language source(srcLanguage);
    Language destination(dstLanguage);

    if (mode == "ct2") {
      MT::CTranslate translator(destination);
      response = translator.translate(data);
      // response = "ct2 translated";
    } else if (mode == "mt5") {
      MT::MT5Translate translator(source, destination);
      response = translator.translate(data);
      // response = "mt5 translated";
    } else if (mode == "opus") {
      MT::OpusTranslate translator(source, destination);
      response = translator.translate(data);
      // response = "opus translated";
    } else if (mode == "smt") {
      MT::StatisticalTranslate translator(source, destination);
      response = translator.translate(data);
      // response = "smt translated";
    } else {
      MT::DummyTranslate translator(source, destination);
      response = translator.translate(data);
      // todo handle malformed data (hopefully not reachable)
    }

    // response = translator.translate(data);

    console->warn(response);

    reply = new zmsg(response.c_str());
  }

  free(reply);
}

void sentiment_worker(int &verbose, Address &address, Port &port) {
  AsyncLogger *console = AsyncLogger::GetInstance();

  std::stringstream uri;
  uri << "tcp://" << address << ":" << port;

  mdwrk session(uri.str(), "sentiment", verbose);
  zmsg *reply = 0;
  Response s;

  while (true) {
    console->warn("Sentimenting works");
    zmsg *request = session.recv(reply);
    if (request == 0) {
      break;  //  Worker was interrupted
    }

    std::string req = std::string(request->body());
    char delim = '\07';

    std::stringstream ss(req);
    std::vector<std::string> parts;
    std::string part;

    while (getline(ss, part, delim)) {
      parts.push_back(part);
    }

    std::string mode = parts[0];
    std::string data = parts[1];

    console->warn(mode, ", ", data);

    if (mode == "nltk") {
      NLTK *instance = new NLTK(data);
      s = instance->getSentiment();
    } else if (mode == "pipeline") {
      Pipeline *instance = new Pipeline(data);
      s = instance->getSentiment();
    } else {
      DummySentiment *instance = new DummySentiment(data);
      s = instance->getSentiment();
      // todo handle malformed data (hopefully not reachable)
    }

    // std::string req = std::string(request->body());
    // std::regex re("(\\w)*\\07(\\w)*");
    // std::smatch matches;
    // if (std::regex_search(req, matches, re)) {
    //   std::string mode = matches.str(1);
    //   std::string data = matches.str(2);
    //   if (mode == "nltk") {
    //     NLTK *instance = new NLTK(data);
    //     s = instance->getSentiment();
    //   } else if (mode == "pipeline") {
    //     Pipeline *instance = new Pipeline(data);
    //     s = instance->getSentiment();
    //   } else {
    //     // todo handle malformed data (hopefully not reachable)
    //   }
    // }

    std::stringstream finished_reply;
    finished_reply << checkValidityString(s.decision) << "\07"
                   << checkValidityFloat(s.score);

    reply = new zmsg(finished_reply.str().c_str());
  }

  free(reply);
}

void detect_worker(int &verbose, Address &address, Port &port) {
  AsyncLogger *console = AsyncLogger::GetInstance();

  std::stringstream uri;
  uri << "tcp://" << address << ":" << port;

  mdwrk session(uri.str(), "detect", verbose);
  zmsg *reply = 0;

  while (true) {
    console->warn("Detect works");
    zmsg *request = session.recv(reply);

    if (request == 0) {
      break;  //  Worker was interrupted
    }

    console->error(request->body());

    std::string req = std::string(request->body());

    std::string response = DetectLanguage::detect(req);

    reply = new zmsg(response.c_str());
  }

  free(reply);
}

void anonymize_worker(int &verbose, Address &address, Port &port) {
  AsyncLogger *console = AsyncLogger::GetInstance();

  std::stringstream uri;
  uri << "tcp://" << address << ":" << port;

  mdwrk session(uri.str(), "anonymize", verbose);
  zmsg *reply = 0;

  while (true) {
    console->warn("Anonymize works");
    zmsg *request = session.recv(reply);

    if (request == 0) {
      break;  //  Worker was interrupted
    }

    console->error(request->body());

    std::string req = std::string(request->body());

    std::string response = Anonymize::anonymize(req);

    reply = new zmsg(response.c_str());
  }

  free(reply);
}

namespace COMMS {
class ZmqCommunication : public Communication {
 private:
  int verbose_flag = 0;

 public:
  ZmqCommunication(Address address, Port port) : Communication(address, port) {}

  void verbose() { verbose_flag = 1; }

  void listen() override {
    AsyncLogger *console = AsyncLogger::GetInstance();

    std::jthread broker_thread(start_broker, std::ref(verbose_flag),
                               std::ref(address), std::ref(port));

    std::jthread ping_thread(ping_worker, std::ref(verbose_flag),
                             std::ref(address), std::ref(port));

    std::jthread translate_thread(translate_worker, std::ref(verbose_flag),
                                  std::ref(address), std::ref(port));

    std::jthread sentiment_thread(sentiment_worker, std::ref(verbose_flag),
                                  std::ref(address), std::ref(port));

    std::jthread detect_thread(detect_worker, std::ref(verbose_flag),
                               std::ref(address), std::ref(port));

    std::jthread anonymize_thread(anonymize_worker, std::ref(verbose_flag),
                                  std::ref(address), std::ref(port));

    std::stringstream listen_info;
    listen_info << "Listening on: " << get_address() << ":" << get_port();

    console->log(listen_info.str());
  }
};
}  // namespace COMMS

#endif  // !ZMQ_COMMUNICATION_HPP