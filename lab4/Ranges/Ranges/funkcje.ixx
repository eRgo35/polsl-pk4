export module funkcje;
import <iostream>;
import <iomanip>;
import <vector>;
import <ranges>;
import <utility>;

export void roman_converter(int number)
{
	std::cout << "Converting " << number << " to roman" << std::endl;
	
	if (number < 0 || number > 3999)
	{
		std::cout << "Number out of bounds!" << std::endl;
		return;
	}


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
}