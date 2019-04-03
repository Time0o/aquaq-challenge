#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>

#include "split.h"
#include "stoi.h"


namespace {

template<typename T>
void increment_each(std::vector<T> &vec, T inc) {
    auto f = [&](T x) { return x + inc; };
    std::transform(vec.begin(), vec.end(), vec.begin(), f);
}

template<typename T>
void increment_each_split(std::vector<T> &vec, T inc1, T inc2) {
    auto vec_copy(vec);
    increment_each(vec, inc1);
    increment_each(vec_copy, inc2);
    vec.insert(vec.end(), vec_copy.begin(), vec_copy.end());
}

}


int main()
{
    // read in deck
    std::string line;
    if (!std::getline(std::cin, line)) {
        std::cerr << "failed to read input\n";
        exit(EXIT_FAILURE);
    }

    auto deck(split(line, ' '));

    // continuously draw from deck
    std::vector<int> points;
    int games_won = 0;

    for (auto const &card : deck) {
        if (points.empty())
            points.push_back(0);

        if (card == "A")
            increment_each_split(points, 1, 11);
        else if (card == "J" || card == "Q" || card == "K")
            increment_each(points, 10);
        else
            increment_each(points, stoi_assert(card));

        if (std::find(points.begin(), points.end(), 21) != points.end()) {
            ++games_won;
            points.clear();
        } else {
            auto pred = [](int p) { return p > 21; };
            auto it = std::remove_if(points.begin(), points.end(), pred);
            points.erase(it, points.end());
        }
    }

    std::cout << games_won << '\n';

    exit(EXIT_SUCCESS);
}
