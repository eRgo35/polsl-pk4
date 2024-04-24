export module median;

import <iostream>;
import <concepts>;
import <ranges>;
import <algorithm>;
import <vector>;

export template<typename T>
concept Array = requires(T container) {
	{ std::sort(container.begin(), container.end()) };
	{ std::begin(container) } -> std::input_or_output_iterator;
	{ std::end(container) } -> std::input_or_output_iterator;
};

export template <Array T>
double calculate_median(T container) {
	std::sort(container.begin(), container.end());
	
	double median = 0;

	if (container.size() % 2)
		median = container.at((container.size() - 1) / 2);
	else
		median = (container.at((container.size() - 1) / 2) + container.at(container.size() / 2)) / 2.00;

	return median;
}