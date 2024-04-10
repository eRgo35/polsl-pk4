import funkcje;

int main()
{
    // useful for debugging
    goto E1;

E1: // Exercise 1
    std::cout << "--- Exercise 1 ---" << std::endl;
    
    matrix m1 = generate_matrix(3);
    matrix m2 = generate_matrix(3);

    matrix mul = multiply_matrix(m1, m2);

    std::cout << "First matrix: " << std::endl;

    print_matrix(m1);

    std::cout << "Second matrix: " << std::endl;

    print_matrix(m2);

    std::cout << "m1 * m2" << std::endl;

    print_matrix(mul);

    matrix m3 = generate_matrix(300);
    matrix m4 = generate_matrix(300);

    matrix mul2 = multiply_matrix(m3, m4);

E2: // Exercise 2
    std::cout << "--- Exercise 2 ---" << std::endl;

    std::string key;
    std::string file;

    std::cout << "Provide a key to search for: ";
    std::cin >> key;

    std::cout << "Provide a path: ";
    std::cin >> file;

    std::cout << "Looking for `" << key << "` in `" << file << "`..." << std::endl;

    count_and_uppercase(key, file);

E3: // Exercise 3
    std::cout << "--- Exercise 3 ---" << std::endl;

    int points = 1000;
    std::cout << "Approximating pi for " << points << "points..." << std::endl;
    double pi = approx_pi(points);
    std::cout << "pi is approx ~ " << pi << std::endl;

E4: // Exercise 4
    std::cout << "--- Exercise 4 ---" << std::endl;

    std::cout << "1BRC" << std::endl
        << "Calculating average temperatures for weather stations" << std::endl;
    
    one_billion_row();

    return 0;
}
