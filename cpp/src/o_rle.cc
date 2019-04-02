#include <cstdlib>
#include <iostream>
#include <string>


std::string::size_type maximum_repeated_substring(std::string const &str)
{
    std::string::size_type res = 0u;

    for (auto start = 0u; start < str.size() - 1; ++start) {
        for (auto len = 1u; len <= (str.size() - start - 1) / 2; ++len) {
            std::string::size_type reps = 1u;

            for (auto offs = start + len;
                 offs <= str.size() - len;
                 offs += len) {

                if (str.substr(start, len) != str.substr(offs, len))
                    break;
                else
                    ++reps;
            }

            res = std::max(res, reps);
        }
    }

    return res;
}


int main()
{
    std::string::size_type res = 0;

    std::string line;
    while (std::getline(std::cin, line))
        res += maximum_repeated_substring(line);

    if (std::cin.bad()) {
        std::cerr << "failed to read input\n";
        exit(EXIT_FAILURE);
    }

    std::cout << res << '\n';

    exit(EXIT_SUCCESS);
}
