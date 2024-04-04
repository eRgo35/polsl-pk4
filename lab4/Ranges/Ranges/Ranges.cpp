import funkcje;

int main()
{
	int number;
	std::string input;
	std::string text;

	goto debug;

	std::cout << "--- Zadanie 1. ---" << std::endl;
	
	std::cout << "Provide a number: ";
	std::cin >> number;
	roman_converter(number);

	std::cout << "--- Zadanie 2. ---" << std::endl;

	std::cout << "Provide a number and chars with spaces: ";
	std::cin >> input;
	text_transformer(input);

	debug:
	std::cout << "--- Zadanie 3. ---" << std::endl;

	std::cout << "Gimme a text: ";
	std::cin >> text;
	find_first_non_repeating_char(text);

	std::cout << "--- Zadanie 4. ---" << std::endl;

	std::cout << "First funny number: ";
	int num1;
	std::cin >> num1;
	std::cout << "Second funny number: ";
	int num2;
	std::cin >> num2;
	check_friends(num1, num2);

	// debug:
	std::cout << "--- Zadanie 5. ---" << std::endl;

	std::cout << "Let's play a game: ";
	fizz_buzz();

	std::cout << "--- Zadanie 6. ---" << std::endl;

	std::cout << "Collatz calculator" << std::endl;
	collatz_calculator();

	std::cout << "--- Zadanie 7. ---" << std::endl;
	std::vector<std::vector<int>> matrix = { { 9, 21, 4 }, { 1, 4, 13 }, { 2, 7, 2 } };
	matrix_calculator(matrix);

	return 0;
}
