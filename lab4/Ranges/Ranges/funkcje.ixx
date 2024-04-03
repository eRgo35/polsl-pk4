#include <ranges>

export module funkcje;
import <iostream>;
import <iomanip>;
import <vector>;
import <utility>;

export void roman_converter(int number)
{
	std::cout << "Converting " << number << " to roman" << std::endl;
	
	if (number < 0 || number > 3999)
	{
		std::cout << "Number out of bounds!" << std::endl;
		return;
	}

	std::vector<std::pair<int, std::string>> roman_table = 
	{
		{3000, "MMM"},
		{2000, "MM"},
		{1000, "M"},
		{900, "CM"},
		{800, "DCCC"},
		{700, "DCC"},
		{600, "DC"},
		{500, "D"},
		{400, "CD"},
		{300, "CCC"},
		{200, "CC"},
		{100, "C"},
		{90, "XC"},
		{80, "LXXX"},
		{70, "LXX"},
		{60, "LX"},
		{50, "L"},
		{40, "XL"},
		{30, "XXX"},
		{20, "XX"},
		{10, "X"},
		{9, "IX"},
		{8, "VIII"},
		{7, "VII"},
		{6, "VI"},
		{5, "V"},
		{4, "IV"},
		{3, "III"},
		{2, "II"},
		{1, "I"},
	};

	std::string numeral;
	for (auto roman : roman_table | std::views::filter([number](auto roman) { return number >= roman.first; }))
	{
		while (number >= roman.first)
		{
			numeral += roman.second;
			number -= roman.first;
		}
	}

	std::cout << numeral << std::endl;

}
export void text_transformer(std::string text)
{
	std::cout << text;
}

export void find_first_non_repeating_char(std::string text)
{
	std::cout << text;
}

export void check_friends(int num1, int num2)
{
	if (num1 < 0 || num2 < 0)
	{
		std::cout << "out of bounds" << std::endl;
		return;
	}
}

export void fizz_buzz()
{
	std::cout << "Fizz-buzz" << std::endl;
	std::string response;
	int counter = 1;
	
	std::cout << "PC > 1" << std::endl;

	do {
		std::cin >> response;
		counter++;


	} while (response != "Stop");
}

export void collatz_calculator()
{
	std::vector<int> numbers;
	char number;

	do {
		std::cout << "add numer (q to stop): ";
		std::cin >> number;

		numbers.push_back(number - '0');
	} while (number != 'q');

	std::cout << "[ ";
	for (int i = 0; i < numbers.size(); i++)
	{
		std::cout << number << " ";
	}
	std::cout << "]" << std::endl;

}

export void matrix_calculator(std::vector<std::vector<int>> matrix)
{
	std::cout << "Matrix calculator" << std::endl;
	
	for (auto r : matrix)
		for (auto w : matrix)


	// metoda Sarrusa
	int det = (matrix[0][0] * matrix[1][1] * matrix[2][2] + matrix[0][1] * matrix[1][2] * matrix[2][0] + matrix[0][2] * matrix[1][0] * matrix[2][1])
				- (matrix[0][2] * matrix[1][1] * matrix[2][0] + matrix[0][0] * matrix[1][2] * matrix[2][1] + matrix[0][1] * matrix[1][0] * matrix[2][2]);

	std::cout << "det(matrix) = " << det << std::endl;
}