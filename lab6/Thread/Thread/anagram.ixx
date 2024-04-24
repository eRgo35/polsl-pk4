#include <ranges>

export module anagram;

import <iostream>;
import <thread>;
import <vector>;
import <map>;
import <functional>;

void char_counter(std::map<char, int> &frequency_map, std::string word) {
	for (char c : word)
		frequency_map[c]++;
}

export bool is_anagram(std::vector<std::string> words) {
	std::vector<std::map<char, int>> frequency_maps(words.size());

	auto it = frequency_maps.begin();
	for (auto& word : words)
		std::jthread w(char_counter, std::ref(*(it++)), word);

	if (std::ranges::adjacent_find(frequency_maps, std::ranges::not_equal_to()) == frequency_maps.end())
		return true;

	return false;
}