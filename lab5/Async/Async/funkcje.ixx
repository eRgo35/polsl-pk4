export module funkcje;

export import <iostream>;
import <vector>;
import <future>;
import <thread>;
import <random>;
import <iomanip>;
import <fstream>;
import <regex>;
import <sstream>;
import <map>;

export import structs;

int generate_number()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(-100, 100);

	return distrib(gen);
}

export void print_matrix(matrix m)
{
	for (auto x : m.data)
	{
		std::cout << "| ";
		for (auto y : x)
		{
			std::cout << std::setw(4) << y << " ";
		}
		std::cout << "|" << std::endl;
	}
	std::cout << std::endl;
}

export matrix generate_matrix(int x, int y)
{
	matrix m;
	m.x = x;
	m.y = y;
	std::vector<std::future<std::vector<int>>> workers;

	for (int i = 0; i < y; i++)
	{
		workers.push_back(std::async(std::launch::async, [x]() {
			std::vector<int> row;
			
			for (int i = 0; i < x; i++)
				row.push_back(generate_number());

			return row;
			}));
	}

	for (auto& worker : workers) {
		m.data.push_back(worker.get());
	}

	for (int i = 0; i < y; i++) 
	{
		std::vector<int> col;
		for (int j = 0; j < x; j++)
		{
			col.push_back(m.data[i][j]);
		}

		m.cols.push_back(col);
	}

	return m;
}

export matrix multiply_matrix(matrix m1, matrix m2)
{
	if (m1.y != m2.x)
	{
		std::cout << "Invalid matrix size!" << std::endl;
		matrix empty;
		empty.x = m1.x;
		empty.y = m1.y;
		std::vector<int> row;
		for (int i = 0; i < empty.x; i++)
			row.push_back(0);

		for (int j = 0; j < empty.y; j++)
			empty.data.push_back(row);

		return empty;
	}
	
	matrix m;
	m.x = m1.x;
	m.y = m1.y;

	std::vector<std::future<std::vector<int>>> workers;

	for (int i = 0; i < m1.y; i++)
	{
		workers.push_back(std::async(std::launch::async, [&m1, &m2, i]() {
			std::vector<int> row;

			for (int j = 0; j < m1.y; j++)
			{
				int value = 0;

				for (int k = 0; k < m1.y; k++) {
					value += m1.data.at(i).at(k) * m2.cols.at(j).at(k);
				}

				row.push_back(value);
			}

			return row;
			}));
	}

	for (auto& worker : workers) {
		m.data.push_back(worker.get());
	}

	return m;
}

export void count_and_uppercase(std::string key, std::string file_path)
{
	std::ifstream file;
	
	std::vector<std::future<std::pair<int, std::string>>> blob;
	
	file.open(file_path);
	
	if (!file.good())
	{
		std::cout << "Well.. something is messsed up..." << std::endl;
		return;
	}

	std::string line;
	std::string loaded_blob;
	int lines = 0;

	while (std::getline(file, line))
	{
		lines++;
		line += "\n";
		loaded_blob += line;
		
		if (lines > 200)
		{
			blob.push_back(std::async(std::launch::async, [&loaded_blob, key]() {
				std::regex re(key);
				std::smatch matches;

				std::regex_search(loaded_blob, matches, re);

				for (auto c : loaded_blob)
					c = (char)std::tolower(c);
				
				// std::cout << loaded_blob;

				std::pair<int, std::string> searched = { matches.length(), loaded_blob };
				return searched;
			}));

			loaded_blob = "";
		}
	}
	file.close();

	std::vector<std::pair<int, std::string>> results;
	int occurences = 0;
	std::stringstream out("");

	for (auto& result : blob)
	{
		std::pair<int, std::string> promise = result.get();

		results.push_back(promise);
		occurences += promise.first;
		out << promise.second;
	}

	std::ofstream fileout;
	fileout.open(file_path);
	
	if (!fileout.good())
	{
		std::cout << "Well.. something is messsed up..." << std::endl;
		return;
	}

	fileout << out.str();

	std::cout << "Found: " << occurences << " occurences!" << std::endl;

	fileout.close();
}

int generate_points(int points) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> distrib(-1.00, 1.00);

	double x;
	double y;

	int match = 0;

	for (int i = 0; i < points; i++) {
		x = distrib(gen);
		y = distrib(gen);
		if (x*x + y*y < 1) {
			match++;
		}
	}
	return match;
};

export double approx_pi(int points)
{
	double pi = 0;
	double x = 0;
	std::vector<std::future<int>> collection;

	for (int i = 0; i < 10; i++)
	{
		collection.push_back(std::async(std::launch::async, generate_points, std::floor(points / 10)));
	}
	
	for (auto& part : collection) {
		x += part.get();
	}

	pi = 4 * x / points;

	return pi;
}

export void one_billion_rows(std::string file_path)
{
	std::ifstream file;

	std::vector<std::future<std::map<std::string, weatherNode>>> blob;

	file.open(file_path);

	if (!file.good())
	{
		std::cout << "Well.. something is messsed up..." << std::endl;
		return;
	}

	std::string line;
	std::string loaded_blob;
	int lines = 0;

	while (std::getline(file, line))
	{
		lines++;
		line += "\n";
		loaded_blob += line;

		if (lines > 500)
		{
			blob.push_back(std::async(std::launch::async, [&loaded_blob]() {
				std::map<std::string, weatherNode> nodes;
				std::stringstream ss(loaded_blob);
				std::string name, temp;
				weatherNode node;

				// std::cout << loaded_blob;

				while (true)
				{
					if (!std::getline(ss, name, ';'))
						break;

					if (!std::getline(ss, temp, '\n'))
						break;

					// std::cout << name << temp << std::endl;

					node.name = name;
					node.temp = std::stoi(temp);

					nodes[name] = node;
				}

				return nodes;
				}));

			loaded_blob = "";
		}
	}

	file.close();

	std::map<std::string, weatherNode> output;
	for (auto& result : blob)
	{
		for (auto& node : result.get())
		{
			output[node.first] = node.second;
		}
	}

	for (auto& result : output)
	{
		std::cout << result.second.name << " got [ " << result.second.temp << " degC ]" << std::endl;
	}
}