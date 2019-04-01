#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <map>
#include <regex>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>


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


static std::vector<std::string> split(std::string const &str, char delim=',')
{
    std::vector<std::string> res;

    std::stringstream ss(str);
    std::string token;

    while (ss.good()) {
        std::getline(ss, token, delim);
        res.push_back(token);
    }

    return res;
}


int main()
{
    // intermediate elo scores of all players
    std::map<std::string, double> elos;

    // CSV column index mapping
    std::map<std::string, std::vector<std::string>::size_type> column_ind;

    std::string line;
    bool first;
    while (std::getline(std::cin, line)) {
        // tokenize line
        std::vector<std::string> tokens(split(line));
        assert(tokens.size() == 3u);

        if (first) {
            // determine column index mapping
            std::set<std::string> columns;
            for (auto i = 0u; i < 3u; ++i) {
                columns.insert(tokens[i]);
                column_ind[tokens[i]] = i;
            }

            // validate column identifiers
            assert(columns == std::set<std::string>({"h", "a", "score"}));

            first = false;
        } else {
            std::string h(tokens[column_ind["h"]]);
            std::string a(tokens[column_ind["a"]]);

            // set initial elo for newly encountered players
            for (auto const &player : {h, a}) {
                if (elos.find(player) == elos.end())
                    elos[player] = INITIAL_elo;
            }

            // parse score
            std::string score(tokens[column_ind["score"]]);

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
