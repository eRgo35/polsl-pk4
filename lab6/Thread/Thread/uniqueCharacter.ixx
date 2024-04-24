export module uniqueCharacter;

import <iostream>;
import <thread>;
import <map>;
import <vector>;
import <mutex>;
import <algorithm>;


std::mutex mux;

void search(std::map<char, int> &frequency_map, std::string chars, int pos) {
	int split = chars.length() / 4;

	chars = chars.substr(pos, split);

	for (char c : chars) {
		std::lock_guard<std::mutex> guard(mux);
		frequency_map[c]++;
	}
	std::this_thread::yield();
}

export char find_unique_char(std::string string) {
	std::vector<std::thread> threads;
	std::map<char, int> frequency_map;

	for (int i = 0; i < 4; ++i) {
		threads.emplace_back(search, std::ref(frequency_map), string, i );
	}

	for (auto& thread : threads) {
		thread.join();
	}

	std::pair<char, int> min = *std::min_element(frequency_map.begin(), frequency_map.end(), [](auto& current, auto& next) {return current.second < next.second;  });

	return min.first;
}