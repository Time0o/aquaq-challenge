#ifndef STOI_H
#define STOI_H

#include <cassert>
#include <string>


int stoi_assert(std::string const &str)
{
    int res;

    bool is_number = true;
    try {
        std::size_t idx;
        res = std::stoi(str, &idx);

        if (idx != str.length())
            is_number = false;
    } catch (std::invalid_argument const &e) {
        is_number = false;
    }

    assert(is_number);

    return res;
}

#endif // STOI_H
