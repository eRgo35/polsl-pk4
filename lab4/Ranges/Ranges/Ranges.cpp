import funkcje;
import <iostream>;
import <vector>;

int main()
{
	std::cout << "Zadanie 1." << std::endl;
	
	std::cout << "Podaj liczbe: ";
	int number;
	std::cin >> number;
	roman_converter(number);

	std::cout << "Zadanie 2." << std::endl;



	std::cout << "Zadanie 3." << std::endl;



	std::cout << "Zadanie 4." << std::endl;



	std::cout << "Zadanie 5." << std::endl;



	std::cout << "Zadanie 6." << std::endl;



	std::cout << "Zadanie 7." << std::endl;

	std::vector<std::vector<int>> matrix = { { 9, 21, 4 }, { 1, 4, 13 }, { 2, 7, 2 } };
	matrix_calculator(matrix);

	return 0;
}
