export module funkcje;
import <iostream>;
import <filesystem>;
import <regex>;

export void find_file_with_ext(std::string path, std::string extension)
{
	std::regex re_ext("(jpg)|(doc)|(pdf)|(txt)|(gif)");
	std::smatch exts_match;
	
	if (!std::regex_match(extension, exts_match, re_ext))
	{
		std::cout << "Unrecognized extension" << std::endl;
		return;
	}

	std::cout << "Recognized extension: " << exts_match.str() << std::endl;

	std::cout << "Found complete" << std::endl;
}

export void backup_folder(std::string source_path, std::string destination_path) 
{
	std::cout << "Backup complete" << std::endl;
}

export void rename_html_files(std::string source_path, std::string destination_path)
{
	bool status = false;

	std::cout << "Operation " << (status ? "completed successfully" : "failed miserably") << std::endl;
}