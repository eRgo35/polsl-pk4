export module structs;

import <vector>;
import <string>;

export struct weatherNode {
	std::string name;
	int temp;
	int min;
	int max;
	int avg;
};

export struct matrix {
	std::vector<std::vector<int>> data;
	int x;
	int y;
	std::vector<std::vector<int>> cols;
};