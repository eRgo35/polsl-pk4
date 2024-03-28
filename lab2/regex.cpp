#include <regex>
#include <iostream>
#include <string>
#include <vector>

// Zadanie 3
bool is_email(const char* input) {
    std::regex email("[A-Za-z0-9.+]+@[A-Za-z0-9]+\\.[a-z]{2,}");
    return std::regex_match(input, email);
};

int main() {
    // Zadanie 1
    std::vector<std::string> numery = { "768923029", "768-923-029", "768 923 029" };
    std::regex numer_1("[\\d]{9}");
    std::regex numer_2("[\\d]{3}-[\\d]{3}-[\\d]{3}");
    std::regex numer_3("[\\d]{3} [\\d]{3} [\\d]{3}");
    std::regex numery_regex[] = { numer_1, numer_2, numer_3 };
    std::vector<std::string> result;
    std::vector<std::string> result2;
    for (std::string numer : numery) {
        std::cout << "Testowany numer: " << numer << std::endl;
        for (int i = 0; i < 3; i++) {
            if (std::regex_match(numer, numery_regex[i])) std::cout << "True" << std::endl;
            else std::cout << "False" << std::endl;
        }
    }
    std::cout << "------------" << std::endl;

    // Zadanie 2
    std::string postCode;
    std::cout << "Podaj kod pocztowy: ";
    std::cin >> postCode;
    std::regex pcode("[\\d]{2}-[\\d]{3}");
    std::cout << "Kod pocztowy jest " << (regex_match(postCode, pcode) ? "" : "nie") << "prawidlowy!" << std::endl;
    std::cout << "-------------" << std::endl;

    // Zadanie 3
    std::string email;
    std::cout << "Podaj email: ";
    std::cin >> email;
    std::cout << "Email jest " << (is_email(email.c_str()) ? "" : "nie") << "prawidlowy!" << std::endl;
    std::cout << "-------------" << std::endl;

    // Zadanie 4
    std::string roll[]{ "2d20+4", "d20", "+4" };
    for (std::string s : roll) {
        int rollAmount = 1;
        int sidesAmount = 20;
        int modifier = 0;
        std::regex r4("([\\d]*)?d([\\d]*)([+|-][\\d]*)?");
        std::smatch s1;
        std::regex_search(s, s1, r4);
        std::string match = s1[0];
        if (s1[1] != "") rollAmount = stoi(s1[1]);
        if (s1[2] != "") sidesAmount = stoi(s1[2]);
        if (s1[3] != "") modifier = stoi(s1[3]);
        std::cout << match << ":" << rollAmount << ":" << sidesAmount << ":" << modifier << std::endl;
    }
    std::cout << "------------" << std::endl;

    // Zadanie 5
    std::string strs = "13 Subscribe to my submersible submarine in sub 37 minutes time.";
    std::string temp = "13 Subscribe to my submersible submarine in sub 37 minutes time.";
    std::regex r5("(sub)([^ ]*)");
    for (std::smatch match; std::regex_search(temp, match, r5);) {
        std::cout << match.str().size() << std::endl;
        temp = match.suffix();
    };
    std::cout << "-----" << std::endl;
    std::regex r6("(\\d*)(?= minutes)");
    std::smatch ma;
    std::regex_search(strs, ma, r6);
    std::cout << ma[1] << std::endl;
    std::regex r7("[a|e|y|u|i|o]");
    std::cout << std::regex_replace(strs, r7, std::string("*")) << std::endl;

    return 0;
}