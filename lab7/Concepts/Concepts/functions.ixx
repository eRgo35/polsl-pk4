#include <ranges>

export module functions;

import <string>;
import <vector>;
import <algorithm>;
import <iostream>;
import <iomanip>;

export template <typename T>
concept Container = requires(T) {
	std::ranges::bidirectional_range<T> && (std::floating_point<T> || std::same_as<T, int>);
};

export template <Container T>
void up_by_five(T container) {
	auto bigger = std::views::transform(container, [](auto number) {
		return number + 5;
	});

	std::cout << "[ ";
	for (auto num : bigger)
		std::cout << std::setw(2) << num << " ";
	std::cout << "]" << std::endl;
}

template <typename U>
concept NameVerify = requires(U) {
	std::same_as<U, std::string>;
};

template <typename V>
concept CollectionVerify = requires(V) {
	std::same_as<V, std::vector<std::string>>;
};

export template<typename U, typename V>
	requires(NameVerify<U>, CollectionVerify<V>)
class Object {
private:
	std::string name;
	std::vector<std::string> collection;
public:
	Object(U name) : name(name) {}

	Object(U name, V collection) : name(name), collection(collection) {}

	std::string get_name() {
		return name;
	}

	std::vector<std::string> get_collection() {
		return collection;
	}
};