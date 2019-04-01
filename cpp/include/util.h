#ifndef UTIL_H
#define UTIL_H

#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>


std::vector<std::string> split(std::string const &str, char delim=',')
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


std::vector<std::vector<std::string>> read_csv(
    std::istream &is, std::vector<std::string> const &columns, char delim=',')
{
    std::vector<decltype(columns.size())> column_indices(columns.size());
    std::vector<std::vector<std::string>> csv;

    // read loop
    std::string line;
    bool first = true;

    while (std::getline(is, line)) {
        std::vector<std::string> tokens(split(line, delim));
        assert(tokens.size() == columns.size());

        if (first) {
            // validate column names and determine column order
            std::set<std::string> columns_actual;

            for (auto i = 0u; i < 3u; ++i) {
                columns_actual.insert(tokens[i]);

                auto column_index = std::find(
                    columns.begin(), columns.end(), tokens[i]) - columns.begin();

                column_indices[i] = column_index;
            }

            assert(columns_actual ==
                   std::set<std::string>(columns.begin(), columns.end()));

            first = false;
        } else {
            // append row
            std::vector<std::string> row(columns.size());

            for (auto i = 0u; i < row.size(); ++i)
                row[column_indices[i]] = tokens[i];

            csv.push_back(row);
        }
    }

    return csv;
}

#endif // UTIL_H
