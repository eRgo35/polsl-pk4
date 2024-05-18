#ifndef DUMMY_COMMUNICATION_HPP
#define DUMMY_COMMUNICATION_HPP

#include <sstream>

#include "../Logger/AsyncLogger.hpp"
#include "./Communication.hpp"

namespace COMMS {
class DummyCommunication : public Communication {
 public:
  DummyCommunication(Address address, int port)
      : Communication(address, port) {}

  void listen() const override {
    AsyncLogger* logger = AsyncLogger::GetInstance("filepath");

    std::stringstream listen_info;
    listen_info << "(dummy) Listening on: " << get_address() << ":"
                << get_port();

    logger->log(listen_info.str());
  }
};
}  // namespace COMMS

#endif  // !DUMMY_COMMUNICATION_HPP
