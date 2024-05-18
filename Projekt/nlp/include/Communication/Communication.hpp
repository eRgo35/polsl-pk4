#ifndef COMMS_HPP
#define COMMS_HPP

#include <string>

#include "../Network/Address.hpp"

namespace COMMS {
class Communication {
 private:
  Address address;
  int port;

 public:
  Communication(Address address, int port) : address(address), port(port) {}

  Address get_address() const { return address; }

  int get_port() const { return port; }

  void set_address(Address new_address) { address = new_address; }

  void set_port(int new_port) { port = new_port; }

  virtual void listen() const = 0;
};
}  // namespace COMMS

#endif  // !COMMS_HPP
