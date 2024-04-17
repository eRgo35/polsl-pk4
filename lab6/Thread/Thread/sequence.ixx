export module sequence;

import <iostream>;
import <vector>;
import <thread>;
import <algorithm>;

void seq(const std::vector<int>& nums, int s_index, int e_index, int& result) {
    std::vector<std::vector<int>> lengths(nums.size(), std::vector<int>(2, 1));

    result = 1;
    for (int i = s_index + 1; i < e_index; ++i) {
        for (int j = 0; j < i; ++j) {
            if (nums[j] < nums[i]) lengths[i][0] = std::max(lengths[i][0], lengths[j][1] + 1);
            if (nums[j] > nums[i]) lengths[i][1] = std::max(lengths[i][1], lengths[j][0] + 1);
        }
        result = std::max(result, std::max(lengths[i][0], lengths[i][1]));
    }
}

export int find_longest_sequence(std::vector<int> nums) {
    std::vector<std::thread> workers;
    std::vector<int> results(8);

    int s_index = 0;
    int e_index = 0;

    for (int i = 0; i < 7; ++i) {
        e_index = s_index + nums.size() / 8;
        workers.emplace_back([&nums, s_index, e_index, i, &results] {
            seq(nums, s_index, e_index, results[i]);
            });
        s_index = e_index;
    }

    workers.emplace_back([&nums, s_index, size = nums.size(), &results] {
        seq(nums, s_index, size, results[7]);
    });

    for (auto& worker : workers) 
        worker.join();

    return *std::max_element(results.begin(), results.end());
}