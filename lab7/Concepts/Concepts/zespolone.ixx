export module zespolone;

import <iostream>;
import <regex>;
import <sstream>;
import <cmath>;

export template <typename C>
concept Complex = requires(C complex) {
	std::integral<C>;
};

export template <Complex C>
void convert_num(C Realis, C Imaginaris) {
	double Z = std::sqrt(Realis*Realis + Imaginaris*Imaginaris);	
	double phi = std::atan(Imaginaris / Realis);

	std::cout << "|" << Z << "|(cos(" << phi << ") + isin(" << phi << "))" << std::endl;
}

export void imaginary_converter() {
	std::string imaginary;

	std::cout << "Provide an complex number: ";

	std::cin >> imaginary;

	
	std::regex re("((\\-?\\d+)(\\-|\\+)(\\d+i))|(\\-?\\d+i?)");
	std::smatch results;

	if (!std::regex_match(imaginary, results, re)) {
		std::cout << "Something is wrong!" << std::endl;
		return;
	}

	//for (auto a : results) {
	//	std::cout << a << std::endl;
	//}

	std::stringstream ss;
	ss << results[3] << results[4];

	double Realis = std::stoi(results[2]);
	double Imaginaris = std::stoi(ss.str());

	std::cout << Realis << Imaginaris << "i" << std::endl;

	convert_num(Realis, Imaginaris);
}