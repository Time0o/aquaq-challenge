#include <cstdlib>
#include <functional>
#include <iostream>
#include <regex>
#include <string>


static std::vector<std::vector<int>> partitions(int n, int target)
{
    std::vector<std::vector<int>> res;
    std::vector<int> buf(n);

    std::function<void(int, int, int, int)>
    recurse = [&](int n, int target, int k, int i) {
        if (n == 0) {
            if (target == 0) {
                std::sort(buf.begin(), buf.end());
                res.push_back(buf);
            }
            return;
        }

        for (int j = k; j < target + 1; ++j) {
            buf[i] = j;
            recurse(n - 1, target - j, j, i + 1);
        }
    };

    recurse(n, target, 0, 0);

    return res;
}


int main()
{
    // parse input
    std::string input;
    if (!getline(std::cin, input) && std::cin.bad()) {
        std::cerr << "failed to read input\n";
        exit(EXIT_FAILURE);
    }

    std::regex reg(R"((\d+) numbers which sum to (\d+))");

    std::cmatch cm;
    if (!std::regex_match(input.c_str(), cm, reg)) {
        std::cerr << "failed to parse input\n";
        exit(EXIT_FAILURE);
    }

    int n = std::stoi(cm[1]);
    int target = std::stoi(cm[2]);

    // generate unique combinations
    auto combinations_unordered = partitions(n, target);

    // generate all unique permutations of unique combinations
    std::stringstream ss;
    for (auto &comb : combinations_unordered) {
        do {
            for (int x : comb)
                ss << x;
        } while (std::next_permutation(comb.begin(), comb.end()));
    }

    // display result
    std::string s(ss.str());
    std::cout << std::count(s.begin(), s.end(), '1') << '\n';

    exit(EXIT_SUCCESS);
}
