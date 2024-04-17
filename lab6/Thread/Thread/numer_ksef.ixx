#define _CRT_SECURE_NO_WARNINGS
export module numer_ksef;

import <iostream>;
import <string>;
import <sstream>;
import <ctime>;
import <chrono>;

export std::string generate_ksef(unsigned int NIP) {
	std::stringstream ksef;
	// struct tm time;
	// std::time_t now = std::time(nullptr);
	// localtime_s(&time, &now);
	
	// auto time_formatted = std::put_time(&time, "%Y%m%d");

	ksef << NIP;
	ksef << "-";
	// ksef << time_formatted;
	ksef << "-";

	return ksef.str();
}