export module structs;

import <vector>;
import <string>;

export struct weatherNode {
	std::string name;
	int temperature;
};

export struct matrix {
	std::vector<std::vector<int>> data;
	int x;
	int y;
};