export module pitagoras;

import <iostream>;
import <concepts>;
import <algorithm>;

export template<typename T>
concept NaturalNumber = requires(T number) {
	std::integral<T> && number > 0;
};

export template <NaturalNumber T> 
bool check_triangle(T a, T b, T c) {
	
	return false;
}