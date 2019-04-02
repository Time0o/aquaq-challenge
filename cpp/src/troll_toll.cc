#include <cstdlib>
#include <iostream>
#include <regex>
#include <string>

#include "graph.h"
#include "util.h"


#define SOURCE "TUPAC"
#define TARGET "DIDDY"


static std::regex const edge_reg(R"((\S+),(\S+),(\d+))");


int main()
{
    UndirectedGraph graph;

    // construct graph
    auto csv = read_csv(std::cin, {"s", "d", "c"});

    for (auto const &row : csv) {
        std::string s(row[0]);
        std::string d(row[1]);
        int w = stoi_assert(row[2]);

        graph.add_edge(s, d, w);
    }

    // find cheapest path
    std::cout << graph.cheapest_path(SOURCE, TARGET) << '\n';

    exit(EXIT_SUCCESS);
}
