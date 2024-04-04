#include <ranges>
#include <iomanip>

export module funkcje;

export import <iostream>;
export import <vector>;
import <string>;
import <regex>;
import <sstream>;

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
	for (auto roman : roman_table | std::views::filter( [number] (auto roman) { return number >= roman.first; }))
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
	std::cout << text << std::endl;
	std::smatch text_parts;

	std::regex re("(\\d{1,2})([\\w\\s]+)");
	if (!std::regex_match(text, text_parts, re))
	{
		std::cout << "bad format :(" << std::endl;
		return;
	}

	std::cout << text_parts[0].str() << std::endl;
	std::cout << text_parts[1].str() << std::endl;

	// std::string cesar = std::views::transform(text, [&move](char c) {});

	std::cout << cesar << std::endl;
}

export void find_first_non_repeating_char(std::string text)
{
	std::cout << text << std::endl;

	std::regex re("[\\d\\w\\s]+");
	if (!std::regex_match(text, re))
	{
		std::cout << "oops, I guess you messed up" << std::endl;
		return;
	}

	bool first = true;
	std::ranges::for_each(text, [text, &first](char c) {
		if (text.find_first_of(c) == text.find_last_of(c) && first)
		{
			std::cout << "non repearing char: " << c << std::endl;
			first = false;
		}
	});
}

export void check_friends(int num1, int num2)
{
	if (num1 < 0 || num2 < 0)
	{
		std::cout << "out of bounds" << std::endl;
		return;
	}

	std::vector<int> divs1;
	std::vector<int> divs2;

	for (int i = 1; i < num1; i++)
	{
		if (num1 % i != 0)
			continue;

		divs1.push_back(i);
	}

	for (int i = 1; i < num2; i++)
	{
		if (num2 % i != 0)
			continue;

		divs2.push_back(i);
	}

	int sum1 = 0;
	std::ranges::for_each(divs1, [&sum1](int divisor) {sum1 += divisor; });
	int sum2 = 0;
	std::ranges::for_each(divs2, [&sum2](int divisor) {sum2 += divisor; });

	if (num1 == sum2 || num2 == sum1)
	{
		std::cout << "we're friends! yay!" << std::endl;
		return;
	}

	std::cout << "we're hating each other :(" << std::endl;
}

export void fizz_buzz()
{
	std::cout << "Fizz-buzz" << std::endl;

	std::string response;
	int count = 1;

	std::cout << "AI> " << count << std::endl;

	std::cout << "You> ";
	std::cin >> response;

	while (response != "Stop")
	{
		if (response == "Fizz" || response == "Buzz" || response == "FizzBuzz") {
			count++;
			count++;
			
			if (count % 5 == 0 && count % 3 == 0)
			{
				std::cout << "AI> Fizz Buzz" << std::endl;
			}
			else if (count % 3 == 0)
			{
				std::cout << "AI> Fizz" << std::endl;
			}
			else if (count % 5 == 0)
			{
				std::cout << "AI> Buzz" << std::endl;
			}
			else {
				std::cout << "AI> " << count << std::endl;
			}

			std::cout << "You> ";
			std::cin >> response;

			continue;
		}
		 
		count++;
		int res = std::stoi(response);

		if (res != count) {
			std::cout << res << count;
			std::cout << "fail! start again!" << std::endl;
			count = 1;
			std::cout << "AI> " << count << std::endl;
			count++;

			std::cout << "You> ";
			std::cin >> response;
		}
		count++;

		if (count % 5 == 0 && count % 3 == 0)
		{
			std::cout << "AI> Fizz Buzz" << std::endl;
		}
		else if (count % 3 == 0)
		{
			std::cout << "AI> Fizz" << std::endl;
		}
		else if (count % 5 == 0)
		{
			std::cout << "AI> Buzz" << std::endl;
		}
		else {
			std::cout << "AI> " << count << std::endl;
		}

		std::cout << "You> ";
		std::cin >> response;
	}

	std::cout << "Thanks for playing!" << std::endl;
}

export void collatz_calculator()
{
	std::cout << "Collatz numbers to check:" << std::endl;

	std::vector<int> numbers;
	int input;

	do {
		std::cin >> input;
		numbers.push_back(input);
	} while (input != 0);

	std::cout << "Collatz steps required:" << std::endl;
	std::ranges::for_each(numbers, [](int num) {

		int steps = 0;

		while (num != 1 && steps < 1000) {
			if (num % 2 != 0)
			{
				num = 3 * num + 1;
			}
			else
			{
				num /= 2;
			}
			steps++;
		}

		return steps;

		std::cout << "Did number: " << num << std::endl;
		std::cout << "In steps: " << steps << std::endl;
	});
}

export void matrix_calculator(std::vector<std::vector<int>> matrix)
{
	std::cout << "Matrix calculator" << std::endl;
	
	std::vector<int> tmatrix;
	std::vector<int> ttmatrix;
	int div = 3;

	for (auto r : matrix)
	{
		std::cout <<  "| ";
		for (auto w : r)
		{
			std::cout << std::setw(2) << w << " ";
			tmatrix.push_back(w);
		}
		std::cout << "|" << std::endl;
	}
	std::cout << std::endl;

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			ttmatrix.push_back(matrix[j][i]);

	// metoda Sarrusa
	int determinant = (matrix[0][0] * matrix[1][1] * matrix[2][2] + matrix[0][1] * matrix[1][2] * matrix[2][0] + matrix[0][2] * matrix[1][0] * matrix[2][1]) - (matrix[0][2] * matrix[1][1] * matrix[2][0] + matrix[0][0] * matrix[1][2] * matrix[2][1] + matrix[0][1] * matrix[1][0] * matrix[2][2]);

	std::cout << "det(matrix) = " << determinant << std::endl;


	int tdiv = div;
	for (auto r : tmatrix | std::views::transform([](auto r) { return (r % 2 == 0) ? 1 : r; }))
	{
		tdiv--;
		// std::cout << "(" << tdiv << ")" << std::endl;
		if (tdiv == 0)
		{
			std::cout << std::setw(2) << r << " ";
			std::cout << "|" << std::endl;
			tdiv = div;
		}
		else if (tdiv == 2)
		{
			std::cout << "| ";
			std::cout << std::setw(2) << r << " ";
		}
		else {
			std::cout << std::setw(2) << r << " ";
		}
	}
	std::cout << std::endl;

	tdiv = div;
	for (auto r : ttmatrix | std::views::transform([](auto r) { return (r % 2 == 0) ? 1 : r; }))
	{
		tdiv--;
		// std::cout << "(" << tdiv << ")" << std::endl;
		if (tdiv == 0)
		{
			std::cout << std::setw(2) << r << " ";
			std::cout << "|" << std::endl;
			tdiv = div;
		}
		else if (tdiv == 2)
		{
			std::cout << "| ";
			std::cout << std::setw(2) << r << " ";
		}
		else {
			std::cout << std::setw(2) << r << " ";
		}
	}
	std::cout << std::endl;
}
