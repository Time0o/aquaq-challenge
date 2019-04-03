#ifndef SPLIT_H
#define SPLIT_H

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

#endif // SPLIT_H
