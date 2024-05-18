#ifndef BEAST_COMMUNICATION_HPP
#define BEAST_COMMUNICATION_HPP

#include <boost/beast.hpp>
#include <sstream>

#include "../Logger/AsyncLogger.hpp"
#include "./Communication.hpp"

namespace COMMS {
class BeastCommunication : public Communication {
 public:
  BeastCommunication(Address address, int port)
      : Communication(address, port) {}

  void listen() const override {
    AsyncLogger* logger = AsyncLogger::GetInstance("filepath");

    std::stringstream listen_info;
    listen_info << "Listening on: " << get_address() << ":" << get_port();

    logger->log(listen_info.str());
  }
};
}  // namespace COMMS

#endif  // !BEAST_COMMUNICATION_HPP
