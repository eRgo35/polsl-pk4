#include <ctime>
export module numer_ksef;

import <iostream>;
import <string>;
import <sstream>;
import <chrono>;
import <regex>;
import <exception>;
import <thread>;
import <algorithm>;
import <mutex>;
import rng;

std::mutex mux;

void generate_timestamp(std::string& times) {
	std::stringstream putted_time;
	std::time_t now = std::time(nullptr);
	struct tm time;
	localtime_s(&time, &now);
	
	putted_time << std::put_time(&time, "%Y%m%d");

	std::lock_guard<std::mutex> lock(mux);
	times += putted_time.str();
	times += "-";
	std::this_thread::yield();
}

void generate_code(std::string& ksef, int length, bool dash) {
	std::string code;
	std::generate_n(std::back_inserter(code), length, [&dash]() { return '0' + generate_number(0, 9); });

	std::lock_guard<std::mutex> lock(mux);
	ksef += code;

	if (dash)
		ksef += "-";

	std::this_thread::yield();
}

void verify_input(std::string& ksef, std::string NIP) {
	std::regex re("\\d{10}");

	if (!std::regex_match(NIP, re))
		throw std::invalid_argument("Invalid NIP provided!");
	
	std::lock_guard<std::mutex> lock(mux);
	ksef += NIP;
	ksef += "-";
	std::this_thread::yield();
}

export std::string generate_ksef(std::string NIP) {
	std::string ksef;
	

	// nie trzeba sprawdzac dalej bo i tak 
	// wyrzuci wyjatek jesli input byl zly
	std::jthread verify(verify_input, std::ref(ksef), NIP);

	verify.join();

	std::jthread timestamp(generate_timestamp, std::ref(ksef));

	timestamp.join();

	std::jthread nums1(generate_code, std::ref(ksef), 6, true);
	std::jthread nums2(generate_code, std::ref(ksef), 6, true);
	
	nums1.join();
	nums2.join();
	
	std::jthread nums3(generate_code, std::ref(ksef), 2, false);
	
	nums3.join();

	return ksef;
}