import funkcje;

int main()
{
    // Exercise 1
    std::cout << "--- Exercise 1 ---" << std::endl;
    
    matrix m1 = generate_matrix(3, 2);
    matrix m2 = generate_matrix(3, 3);

    matrix mul = multiply_matrix(m1, m2);

    std::cout << "First matrix: " << std::endl;

    print_matrix(m1);

    std::cout << "Second matrix: " << std::endl;

    print_matrix(m2);

    std::cout << "m1 * m2" << std::endl;

    print_matrix(mul);

    std::cout << "---------------" << std::endl;

    matrix m3 = generate_matrix(2, 2);
    matrix m4 = generate_matrix(2, 2);

    matrix mul2 = multiply_matrix(m3, m4);

    std::cout << "First matrix: " << std::endl;

    print_matrix(m3);

    std::cout << "Second matrix: " << std::endl;

    print_matrix(m4);

    std::cout << "m3 * m4" << std::endl;

    print_matrix(mul2);

    matrix m5 = generate_matrix(300, 300);
    matrix m6 = generate_matrix(300, 300);

    matrix mul3 = multiply_matrix(m5, m6);

    // Exercise 2
    std::cout << "--- Exercise 2 ---" << std::endl;

    std::string key;
    std::string file;

    std::cout << "Provide a key to search for: ";
    std::cin >> key;

    std::cout << "Provide a path: ";
    std::cin >> file;

    std::cout << "Looking for `" << key << "` in `" << file << "`..." << std::endl;

    count_and_uppercase(key, file);

    // Exercise 3
    std::cout << "--- Exercise 3 ---" << std::endl;

    int points = 1000;
    std::cout << "Approximating pi for " << points << " points..." << std::endl;
    double pi = approx_pi(points);
    std::cout << "pi is approx ~ " << pi << std::endl;

    // Exercise 4
    std::cout << "--- Exercise 4 ---" << std::endl;

    std::cout << "1BRC" << std::endl
        << "Calculating average temperatures for weather stations" << std::endl;
    
    std::cout << "Provide a path: ";
    std::cin >> file;

    one_billion_rows(file);

    return 0;
}