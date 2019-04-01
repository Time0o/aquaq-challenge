#include <cctype>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>


int main()
{
    std::string input;
    if (!std::getline(std::cin, input) && std::cin.bad()) {
        std::cerr << "failed to read input\n";
        exit(EXIT_FAILURE);
    }

    for (char &c : input) {
        if (!isxdigit(c))
            c = '0';
    }

    input += std::string(3 - input.length() % 3, '0');
    auto chunk_size = input.length() / 3;

    std::stringstream ss;
    for (int i = 0; i < 3; ++i)
        ss << input[i * chunk_size] << input[i * chunk_size + 1];

    std::cout << ss.str() << '\n';

    exit(EXIT_SUCCESS);
}
