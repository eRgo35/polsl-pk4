#ifndef PORT_HPP
#define PORT_HPP

#include <concepts>
#include <exception>
#include <ranges>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

template<typename T>
concept PortConcept = requires(T t, int port) {
    { t.verify(port) } -> std::same_as<bool>;
};

class Port {
 private:
  int port = 5555;

  void parse(int port) {
    if (port < 0 || port > 65535) {
      throw std::invalid_argument("Provided port is invalid");
    }
    this->port = port;
  }

 public:
  Port(int port) { parse(port); }

  int get() { return port; }

  void set(int port) { parse(port); }

  friend std::istream &operator>>(std::istream &is, Port port) {
    int incoming_port;
    is >> incoming_port;
    port.set(incoming_port);
    return is;
  }

  friend std::ostream &operator<<(std::ostream &os, Port port) {
    os << port.get();
    return os;
  }
};

#endif  // !PORT_HPP