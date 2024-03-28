export module menu;
import <iostream>;
import <regex>;
import funkcje;
import gra;

export void menu()
{
	std::string option;

	do {
		std::cout << "Menu glowne: " << std::endl
			<< "1. Wyszukaj pliki o podanym rozszerzeniu" << std::endl
			<< "2. Wyszukaj pliki html i zamien ich nazwe" << std::endl
			<< "3. Utworz kopie zapasowa zawartosci foderu" << std::endl
			<< "4. Gra: szukanie klucza" << std::endl
			<< "5. Wyjdz" << std::endl;
		
		std::cout << "Wybierz opcje: ";

		std::cin >> option;
		
		std::regex selection("([1-5])");
		std::smatch res;

		if (!std::regex_match(option, res, selection))
		{
			std::cout << "incorrect" << std::endl;
			continue;
		}
		
		if (res.str() == "1")
		{
			std::string path;
			std::cout << "Podaj sciezke: ";
			std::cin >> path;

			std::string ext;
			std::cout << "Podaj rozszerzenie: ";
			std::cin >> ext;

			find_file_with_ext(path, ext);
		}
		
		if (res.str() == "2")
		{
			std::string source_path;
			std::cout << "Podaj sciezke zrodlowa: ";
			std::cin >> source_path;

			std::string destination_path;
			std::cout << "Podaj sciezke docelowa: ";
			std::cin >> destination_path;

			rename_html_files(source_path, destination_path);
		}
		
		if (res.str() == "3")
		{
			std::string source_path;
			std::cout << "Podaj sciezke zrodlowa: ";
			std::cin >> source_path;

			std::string destination_path;
			std::cout << "Podaj sciezke docelowa: ";
			std::cin >> destination_path;

			backup_folder(source_path, destination_path);
		}
		
		if (res.str() == "4")
		{
			std::string path;
			std::cout << "Podaj sciezke: ";
			std::cin >> path;

			std::string keyword;
			std::cout << "Podaj slowo kluczowe: ";
			std::cin >> keyword;

			find_key_game(path, keyword);
		}
		
		if (res.str() == "5")
		{
			std::cout << "exiting..." << std::endl;
		}

		std::cout << std::endl;
	} while (option != "5");
}