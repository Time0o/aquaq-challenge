#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <utility>
#include <vector>

#include "util.h"


enum { INITIAL_elo = 1200 };

static std::regex const score_reg(R"((\d+)-(\d+))");


static double expected_win_rate(double elo_a, double elo_b)
{
    return 1 / (1 + std::pow(10, (elo_b - elo_a) / 400));
}


static void update_elo(double &elo_winner, double &elo_loser)
{
    double points = 20 * (1 - expected_win_rate(elo_winner, elo_loser));

    elo_winner += points;
    elo_loser -= points;
}


int main()
{
    // intermediate elo scores of all players
    std::map<std::string, double> elos;

    // read match results and update elo scores
    auto csv = read_csv(std::cin, {"h", "a", "score"});

    for (auto const &row : csv) {
        std::string h(row[0]);
        std::string a(row[1]);

        // set initial elo for newly encountered players
        for (auto const &player : {h, a}) {
            if (elos.find(player) == elos.end())
                elos[player] = INITIAL_elo;
        }

        // parse score
        std::string score(row[2]);

        std::cmatch cm;
        if (!std::regex_match(score.c_str(), cm, score_reg)) {
            std::cerr << "failed to parse '" << score << "'\n";
            exit(EXIT_FAILURE);
        }

        // update elo
        double elo_h = elos[h];
        double elo_a = elos[a];

        if (std::stoi(cm[1]) > std::stoi(cm[2]))
            update_elo(elo_h, elo_a);
        else
            update_elo(elo_a, elo_h);

        elos[h] = elo_h;
        elos[a] = elo_a;
    }

    if (std::cin.bad()) {
        std::cerr << "failed to read input\n";
        exit(EXIT_FAILURE);
    }

    // calculate difference between maximum and minimum elo
    typedef std::pair<std::string, double> elo_entry;

    auto minmax_elo = std::minmax_element(
        elos.begin(),
        elos.end(),
        [](elo_entry const &left, elo_entry const &right) {
            return left.second < right.second;
        }
    );

    int min_elo = static_cast<int>(minmax_elo.first->second);
    int max_elo = static_cast<int>(minmax_elo.second->second);

    std::cout << max_elo - min_elo << '\n';

    exit(EXIT_SUCCESS);
}
