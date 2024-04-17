#include <random>

import anagram;
import numer_ksef;
import uniqueCharacter;
import sequence;
import median;

import <vector>;
import <string>;
import <iostream>;

int generate_number(int min, int max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(min, max);

	return distrib(gen);
}

int main()
{
	// Zadanie 1
	std::vector<std::string> words = {"thread", "daerht", "hterda", "htread"};

	bool check = is_anagram(words);

	std::cout << "Podany ciag " << (check ? "" : "nie") << " ma " << (check ? "anagramy!" : "anagramow!") << std::endl;

	// Zadanie 2

	unsigned int nip = 0;
	
	std::cout << "Podaj swoj numer NIP: ";
	std::cin >> nip;

	std::string ksef = generate_ksef(nip);
	std::cout << "Numer KSEF: " << ksef << std::endl;

	// Zadanie 3

	std::string ciag_liter = "aabcdgdg";

	char unique = find_unique_char(ciag_liter);

	std::cout << "Unikalny znak w ciagu `" << ciag_liter << "` to litera: `" << unique << "`." << std::endl;

	// Zadanie 4

	std::vector<int> kontener;
	
	for (int i = 0; i < 100; i++)
		kontener.push_back(generate_number(0, 1000));

	int longest = find_longest_sequence(kontener);

	std::cout << "Najdluzsza sekwencja ma dlugosc: " << longest << "!" << std::endl;

	// Zadanie 5

	std::vector<int> kontener2;

	for (int i = 0; i < 1000; i++)
		kontener2.push_back(generate_number(0, 100));

	double median = find_median(kontener2);
	double dominant = find_dominant(kontener2);

	std::cout << "Mediana zbioru wynosi: " << median << std::endl;
	std::cout << "Dominanta zbioru wynosi: " << dominant << std::endl;

	return 0;
}