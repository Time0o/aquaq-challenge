#include <cassert>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <regex>
#include <string>
#include <vector>

#include "util.h"


#define SOURCE "TUPAC"
#define TARGET "DIDDY"


static std::regex const edge_reg(R"((\S+),(\S+),(\d+))");


struct Graph {
    void add_edge(std::string const &source,
                  std::string const &target,
                  int weight) {

        adjacencies[source].push_back({target, weight});
        adjacencies[target].push_back({source, weight});
    }

    int cheapest_path(std::string const &source,
                      std::string const &target) {

        // nodes
        struct Node {
            Node() {}

            Node(std::string name, int initial_weight=INT_MAX)
                : name(name), tentative_weight(initial_weight) {}

            std::string name;
            int tentative_weight;
        };

        std::map<std::string, Node> nodes;

        // node visitation status
        std::map<std::string, bool> visited;

        // node priority queue
        auto comp = [](Node const &lhs,
                       Node const &rhs) {

            return lhs.tentative_weight > rhs.tentative_weight;
        };

        std::priority_queue<
            Node,
            std::vector<Node>,
            decltype(comp)
        > node_queue(comp);

        // initialize data structures
        for (auto const &adj : adjacencies) {
            Node node;
            if (adj.first == source)
                node = Node(adj.first, 0);
            else
                node = Node(adj.first);

            nodes[adj.first] = node;
            visited[adj.first] = false;

            node_queue.push(node);
        }

        // Dijkstra's algorithm
        while (!node_queue.empty()) {
            auto current(node_queue.top());
            node_queue.pop();

            assert(current.tentative_weight < INT_MAX);

            for (auto const &edge : adjacencies[current.name]) {
                auto neighbour(nodes[edge.first]);

                if (visited[neighbour.name])
                    continue;

                neighbour.tentative_weight = std::min(
                    neighbour.tentative_weight,
                    current.tentative_weight + edge.second);

                node_queue.push(neighbour);
            }

            visited[current.name] = true;

            if (current.name == target)
                return current.tentative_weight;
        }

        assert(false);
    }

    std::map<std::string, std::vector<std::pair<std::string, int>>> adjacencies;
};


int main()
{
    Graph graph;

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
