#ifndef ADDRESS_HPP
#define ADDRESS_HPP

#include <exception>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

class Address {
 private:
  std::vector<int> ip = {0, 0, 0, 0};

  std::vector<std::string> tokenizer(std::string string, char separator) {
    std::vector<std::string> results;

    std::stringstream stream(string);
    std::string word;

    while (!stream.eof()) {
      std::getline(stream, word, separator);
      results.push_back(word);
    }

    return results;
  }

  bool verify(std::string address) {
    std::regex ip_regex(
        "^((25[0-5]|(2[0-4]|1\\d|[1-9]|)\\d)\\.){3}(25[0-5]|(2[0-4]|1\\d|[1-9]|"
        ")\\d)$");

    bool verification = std::regex_match(address, ip_regex);

    return verification;
  }

 public:
  Address(std::string address) {
    if (!verify(address))
      throw std::invalid_argument("Provided address is invalid");

    std::vector<std::string> octs = tokenizer(address, '.');

    for (int i = 0; i < 4; i++) ip.at(i) = std::stoi(octs.at(i));
  }

  std::string get() {
    std::stringstream ip_address;

    for (int i = 0; i < 3; i++) ip_address << ip.at(i) << ".";
    ip_address << ip.at(3);

    return ip_address.str();
  }

  void set(std::string address) {
    if (!verify(address))
      throw std::invalid_argument("Provided address is invalid");

    std::vector<std::string> octs = tokenizer(address, '.');

    for (int i = 0; i < 4; i++) ip.at(i) = std::stoi(octs.at(i));
  }

  friend std::istream &operator>>(std::istream &is, Address address) {
    std::string incoming_address;
    is >> incoming_address;

    address.set(incoming_address);

    return is;
  }

  friend std::ostream &operator<<(std::ostream &os, Address address) {
    os << address.get();

    return os;
  }
};

#endif  // !ADDRESS_HPP
