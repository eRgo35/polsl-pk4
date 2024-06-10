#ifndef COMMS_HPP
#define COMMS_HPP

#include <string>

#include "../Network/Address.hpp"
#include "../Network/Port.hpp"

namespace COMMS {
class Communication {
 protected:
  Address address;
  Port port;

 public:
  Communication(Address address, Port port) : address(address), port(port) {}

  Address get_address() const { return address; }

  Port get_port() const { return port; }

  void set_address(Address new_address) { address = new_address; }

  void set_port(Port new_port) { port = new_port; }

  virtual void listen() = 0;
};
}  // namespace COMMS

#endif  // !COMMS_HPP
