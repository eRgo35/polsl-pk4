import pitagoras;
import zespolone;
import bmi;
import median;
import functions;
import library;

import <iomanip>;
import <vector>;
import <iostream>;
import <string>;

int main()
{
    std::cout << "--- Exercise 1 ---" << std::endl;
    int a = 3;
    int b = 4;
    int c = 5;
    std::cout << check_triangle(a, b, c);

    std::cout << "--- Exercise 2 ---" << std::endl;

    imaginary_converter();

    std::cout << "--- Exercise 3 ---" << std::endl;

    bmi();

    std::cout << "--- Exercise 4 ---" << std::endl;

    std::vector<int> numbers = { 6, 5, 4, 3, 2, 1 };
    std::vector<int> numbers2 = { 5, 4, 3, 2, 1 };

    std::cout << calculate_median(numbers) << std::endl;
    std::cout << calculate_median(numbers2) << std::endl;

    std::cout << "--- Exercise 5 ---" << std::endl;

    start_library();

    std::cout << "--- Exercise 6 ---" << std::endl;

    std::vector<int> nums = {4, 1, 3, 7, 9};
    
    std::cout << "[ ";
    for (auto num : nums)
        std::cout << std::setw(2) << num << " ";
    std::cout << "]" << std::endl;
    
    up_by_five(nums);

    std::cout << "--- Exercise 7 ---" << std::endl;

    std::string name = "Some name";
    std::vector<std::string> collection = { "some", "interesting", "collection" };
    Object funny(name, collection);

    std::cout << funny.get_name() << std::endl;

    std::cout << "[ ";
    for (auto text : funny.get_collection())
        std::cout << text << " ";
    std::cout << "]" << std::endl;

    return 0;
}
