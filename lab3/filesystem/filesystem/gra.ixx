export module gra;
import <iostream>;
import <fstream>;
import <filesystem>;

export void find_key_game(std::string path, std::string keyword)
{
	std::cout << "Let the game begin!" << std::endl;

	for (const auto& entry : std::filesystem::recursive_directory_iterator(path))
	{
		if (!is_regular_file(entry.path())) {
			continue;
		}

		if (entry.path().extension() != ".txt") {
			continue;
		}

		std::ifstream file(entry.path());

		if (!file.is_open()) {
			std::cout << "Error reading file(s)" << std::endl;
		}

		std::string line;

		while (std::getline(file, line)) {
			if (line.find(keyword) == std::string::npos) {
				std::cout << "No keyword found" << std::endl;
				continue;
			}

			std::cout << "Found keyword: " << keyword << std::endl
				<< "inside: " << entry.path() << std::endl
				<< "filename: " << entry.path().filename() << std::endl
				<< "filesize: " << file_size(entry.path()) << std::endl;
			break;
		}

		file.close();
	}
}