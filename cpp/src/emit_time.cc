#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <regex>
#include <string>
#include <utility>
#include <vector>


static std::regex const time_reg(R"((\d+):(\d+):(\d+))");


static int reverse_digits(int n)
{
    char buf[3];
    std::sprintf(buf, "%02d", n);

    char buf_reverse[3];
    buf_reverse[0] = buf[1];
    buf_reverse[1] = buf[0];
    buf_reverse[2] = '\0';

    return std::stoi(buf_reverse);
}


static int to_seconds(int hours, int minutes, int seconds)
{
    return 60 * (60 * hours + minutes) + seconds;
}


int main()
{
    // pre-calculate all possible palindromic times in seconds
    std::vector<std::pair<int, std::string>> palindromic_times;
    char palindromic_time[9];

    for (int hours = 0; hours <= 23; ++hours) {
        int seconds = reverse_digits(hours);

        if (seconds > 59)
            continue;

        for (int minutes = 0; minutes <= 55; minutes += 11) {
            std::sprintf(
                palindromic_time, "%02d:%02d:%02d", hours, minutes, seconds);

            palindromic_times.push_back({
                to_seconds(hours, minutes, seconds),
                palindromic_time
            });
        }
    }

    // final sum of differences
    int res = 0;

    // parse input
    std::string line;
    while (std::getline(std::cin, line)) {
        // parse time
        std::cmatch cm;
        if (!std::regex_match(line.c_str(), cm, time_reg)) {
            std::cerr << "failed to parse '" << line << "'\n";
            exit(EXIT_FAILURE);
        }

        int hours = std::stoi(cm[1]);
        int minutes = std::stoi(cm[2]);
        int seconds = std::stoi(cm[3]);

        int time = to_seconds(hours, minutes, seconds);

        // find closest palindromic time
        auto comp = [](std::pair<int, std::string> const &pt, int t) {
            return pt.first < t;
        };

        auto it = std::lower_bound(palindromic_times.begin(),
                                   palindromic_times.end(),
                                   time,
                                   comp);

        if (it == palindromic_times.begin())
            res += time;
        else if (it == palindromic_times.end())
            res += std::min(time - palindromic_times.back().first,
                            to_seconds(24, 0, 0) - time);
        else
            res += std::min(time - (it - 1)->first, it->first - time);
    }

    if (std::cin.bad()) {
        std::cerr << "failed to read input\n";
        exit(EXIT_FAILURE);
    }

    std::cout << res << '\n';

    exit(EXIT_SUCCESS);
}
