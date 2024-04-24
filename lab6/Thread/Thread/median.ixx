export module median;

import <iostream>;
import <vector>;
import <map>;
import <algorithm>;
import <mutex>;

std::mutex mux;

export void find_median(double &median, std::vector<int> &nums) {
	std::vector<int> sorted(nums.size());

	std::lock_guard<std::mutex> lock(mux);
	std::sort(nums.begin(), nums.end());

	if (sorted.size() % 2) {
		median = sorted.at(sorted.size() / 2);
		return;
	}
	
	median = ((sorted.at(sorted.size() / 2 - 1) + sorted.at(sorted.size() / 2)) / 2.0);
}

export void find_dominant(int &dominant, std::vector<int> &nums) {
	std::map<int, int> frequency_map;

	std::lock_guard<std::mutex> lock(mux);
	for (auto& num : nums)
		frequency_map[num]++;

	std::pair<int, int> max = *std::max_element(frequency_map.begin(), frequency_map.end(), [](auto& current, auto& next) {return current.second < next.second;  });

	dominant = max.first;
}