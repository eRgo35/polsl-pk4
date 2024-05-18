#include <string>
#include <thread>

#include "../include/Communication/Beast.hpp"
#include "../include/Communication/Dummy.hpp"
#include "../include/Engine/Language.hpp"
#include "../include/Logger/AsyncLogger.hpp"
#include "../include/Translate/Dummy.hpp"
#include "../include/Translate/Statistical.hpp"
#include "../include/Engine/Trainer.hpp"
#include "../include/Communication/rpc.hpp"
#include "../include/Communication/rpcWorker.hpp"

void startBroker(int &verbose){
  s_version_assert (4, 0);
  s_catch_signals ();
  broker brk(verbose);
  brk.bind ("tcp://*:5555");
  brk.start_brokering();
  if (s_interrupted) printf ("W: interrupt received, shutting down...\n");
  
}

void pingWorker(int &verbose, AsyncLogger* log){
  mdwrk session ("tcp://localhost:5555", "ping", verbose);
  zmsg *reply = 0;
  while (1) {
    log->log("Reply out:");
    zmsg *request = session.recv (reply);
    if (request == 0) {
      break;              //  Worker was interrupted
    }
      reply = request;
  }
  free(reply);
}


int main(int argc, char** argv) {
  AsyncLogger* logger = AsyncLogger::GetInstance("filepath");

  logger->log("NLP Platform");
  logger->log("Version 1.0.0");
  logger->log("Copyright(c) 2024 Michał Czyż, Dawid Głąb");
  logger->log("All Rights Reserved");

  Address address("127.0.0.1");
  Address apipa("169.254.10.10");
  COMMS::BeastCommunication comms(address, 4200);
  COMMS::DummyCommunication dummycomms(apipa, 3366);
  
  // Begin Broker and Workers
  //int verbose = (argc > 1 && strcmp (argv [1], "-v") == 0);
  int verbose = 1;
  std::jthread broker_thread(startBroker, std::ref(verbose));
  std::jthread worker_thread(pingWorker, std::ref(verbose), std::ref(logger));

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

  // // std::string save_path = "/home/mike/Projects/nlp-platform/nlp/stat_model_v1.smt";
  // // logger->log("Model path: " + save_path);
  // // model.save(save_path);
 
  // MT::StatisticalTranslate stats(src, des);
  // stats.use(model, model);
  // logger->log(stats.translate("I just want to tell you how I am feeling"));

  return 0;
}
