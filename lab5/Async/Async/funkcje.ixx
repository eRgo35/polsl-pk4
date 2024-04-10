export module funkcje;

export import <iostream>;
import <vector>;
import <future>;
import <thread>;
import <random>;

export import structs;

export void print_matrix(matrix m)
{
	for (auto x : m.data)
	{
		std::cout << "| ";
		for (auto y : x)
		{
			std::cout << y << " ";
		}
		std::cout << "|" << std::endl;
	}
	std::cout << std::endl;
}

export matrix generate_matrix(int size)
{
	matrix m;

	std::random_device rd; 
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(-100, 100);

	for (int i = 0; i < size; i++)
		m.data[i][0] = distrib(gen);


	return m;
}

export matrix multiply_matrix(matrix m1, matrix m2)
{
	if (m1.data.size() != m2.data.size())
		return m1;



	// placeholder
	return m1;
}

export void count_and_uppercase(std::string key, std::string file)
{

}

export double approx_pi(int points)
{
	return 3.14159;
}

export void one_billion_row()
{

}