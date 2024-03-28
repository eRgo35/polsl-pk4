export module funkcje;
import <chrono>;
import <filesystem>;
import <format>;
import <fstream>;
import <iostream>;
import <regex>;

export void find_file_with_ext(std::string path, std::string extension)
{
	std::regex re_ext("(jpg|doc|pdf|txt|gif)");
	std::regex re("*\\." + extension);
	std::smatch exts_match;

	if (!std::regex_match(extension, exts_match, re_ext))
	{
		std::cout << "Unrecognized extension" << std::endl;
		return;
	}

	std::cout << "Recognized extension: " << exts_match.str() << std::endl;

	for (const auto& entry : std::filesystem::recursive_directory_iterator(path))
	{
		if (!is_regular_file(entry.path())) {
			continue;
		}

		std::string filename = entry.path().filename().string();
		std::cout << filename << std::endl;

		// this regex has unexpected behavior
		if (std::regex_match(filename, re))
		{
			std::cout << "filename: " << entry.path().filename().string() << std::endl
				<< "filesize: " << file_size(entry.path()) << std::endl;
		}
	}

	std::cout << "Found complete" << std::endl;
}

export void backup_folder(std::string source_path, std::string destination_path) 
{
	std::filesystem::path source(source_path);
	std::filesystem::path destination(destination_path);

	std::cout << "Copying from: " << source.string() << std::endl;
	std::cout << "into: " << destination.string() << std::endl;

	std::filesystem::copy(source, destination, std::filesystem::copy_options::recursive);

	std::cout << "Backup complete" << std::endl;
}

export void rename_html_files(std::string source_path, std::string destination_path)
{
	for (const auto& entry : std::filesystem::recursive_directory_iterator(source_path))
	{
		if (!is_regular_file(entry.path())) {
			continue;
		}

		std::string filename = entry.path().filename().string();
		std::string filesize = std::to_string(file_size(entry.path()));

		if (!filename.ends_with(".html")) {
			continue;
		}

		std::cout << filename << std::endl;

		// unrecoverable error importing header unit 'c:\program files\microsoft visual studio\2022\community\vc\tools\msvc\14.39.33519\include\filesystem'.Specialization of 'std::chrono::_Make_unique_tzdb_info' with arguments '__std_tzdb_time_zones_info *__std_tzdb_get_time_zones(void) noexcept,'
		// I give up
		std::filesystem::file_time_type mod_time = std::filesystem::last_write_time(entry.path());
		// std::cout << std::format("Last modified: {}", mod_time) << std::endl;
		
		std::filesystem::copy_file(entry.path(), destination_path + "\\" + filesize + ".html", std::filesystem::copy_options::overwrite_existing);

		std::cout << "Operation completed" << std::endl;
	}
}