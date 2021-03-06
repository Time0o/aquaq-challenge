#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "stoi.h"


enum { BIG_BASE = static_cast<uint32_t>(1e9) };


static void big_mult(std::vector<int> nums)
{
    std::vector<uint32_t> big(nums.size());
    big[0] = 1u;

    uint64_t carry = 0u;
    uint64_t tmp;

    for (unsigned n : nums) {
        for (auto i = 0u; i < big.size(); ++i) {
            tmp = (uint64_t)n * (uint64_t)big[i] + carry;
            big[i] = (uint32_t)(tmp % BIG_BASE);
            carry = (uint32_t)(tmp / BIG_BASE);
        }

        if (carry > 0u)
            big.push_back((uint32_t)(carry));
    }

    bool first = false;
    for (auto i = big.rbegin(); i != big.rend(); ++i) {
        if (!first) {
            if (*i == 0u)
                continue;

            first = true;
        }
        std::cout << *i;
    }
    std::cout << '\n';
}


int main()
{
    std::vector<int> nums;

    std::string line;
    while (getline(std::cin, line))
        nums.push_back(stoi_assert(line));

    if (std::cin.bad()) {
        std::cerr << "failed to read input\n";
        exit(EXIT_FAILURE);
    }

    big_mult(nums);

    exit(EXIT_SUCCESS);
}
