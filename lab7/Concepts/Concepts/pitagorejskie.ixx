export module pitagoras;

import <iostream>;
import <concepts>;
import <algorithm>;

export template<typename T>
concept NaturalNumber = requires(T number) {
	std::integral<T>;
	{ number > 0 } -> std::convertible_to<bool>;
};

export template <NaturalNumber T> 
bool check_triangle(T a, T b, T c) {
	if (a * a + b * b == c * c)
		return true;

	return false;
}
