#include <cstdlib>
#include <iostream>
#include <map>
#include <numeric>
#include <vector>


int main()
{
    // read records
    std::vector<int> records;

    int x;
    while (std::cin >> x)
        records.push_back(x);

    if (std::cin.bad() || !std::cin.eof()) {
        std::cerr << "failed to read input\n";
        exit(EXIT_FAILURE);
    }

    // count occurences of each record
    std::map<int, int> occurences;
    for (int x : records)
        ++occurences[x];

    // clean records
    std::vector<int> result;

    decltype(records.size()) i = 0u;
    while (i < records.size()) {
        x = records[i];
        result.push_back(x);

        while (occurences[x] > 1)
            --occurences[records[++i]];

        ++i;
    }

    // sum up records
    std::cout << std::accumulate(result.begin(), result.end(), 0) << '\n';

    exit(EXIT_SUCCESS);
}
