#ifndef ADDRESS_HPP
#define ADDRESS_HPP

#include <concepts>
#include <exception>
#include <ranges>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

template <typename T>
concept AddressConcept = requires(T t, const std::string &address) {
  { t.verify(address) } -> std::same_as<bool>;
};

class Address {
 private:
  std::vector<int> ip = {0, 0, 0, 0};

  bool verify(std::string &address) const {
    const std::regex ip_regex(
        "^((25[0-5]|(2[0-4]|1\\d|[1-9]|)\\d)\\.){3}(25[0-5]|(2[0-4]|1\\d|[1-9]|"
        ")\\d)$");

    return std::regex_match(address, ip_regex);
  }

  std::vector<std::string> tokenizer(const std::string &string,
                                     char separator) {
    std::vector<std::string> tokens;

    std::ranges::split_view splits{string, separator};
    for (auto &&split : splits) {
      tokens.emplace_back(split.begin(), split.end());
    }

    return tokens;
  }

  std::vector<int> convert_int(const std::vector<std::string> &octs) {
    std::vector<int> int_octs;

    std::ranges::transform(
        octs, std::back_inserter(int_octs),
        [](const std::string &oct) { return std::stoi(oct); });

    return int_octs;
  }

  void parse_address(std::string &address) {
    if (address == "localhost") {
      ip = {127, 0, 0, 1};
      return;
    }

    if (!verify(address))
      throw std::invalid_argument("Provided address is invalid");

    std::vector<std::string> octs = tokenizer(address, '.');
    ip = convert_int(octs);
  }

 public:
  Address(std::string address) { parse_address(address); }

  std::string get() {
    return std::format("{}.{}.{}.{}", ip[0], ip[1], ip[2], ip[3]);
  }

  void set(std::string address) { parse_address(address); }

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
