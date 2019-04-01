#include <cstdlib>
#include <iostream>
#include <string>


static int const room[6][6] {
    {0, 0, 1, 1, 0, 0},
    {0, 1, 1, 1, 1, 0},
    {1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1},
    {0, 1, 1, 1, 1, 0},
    {0, 0, 1, 1, 0, 0}
};


int main()
{
    std::string directions;
    std::cin >> directions;

    int result = 0;

    int x = 2, y = 0;
    for (char d : directions) {
        switch (d) {
        case 'U':
            if (y > 0 && room[y - 1][x])
                --y;
            break;
        case 'D':
            if (y < 5 && room[y + 1][x])
                ++y;
            break;
        case 'L':
            if (x > 0 && room[y][x - 1])
                --x;
            break;
        case 'R':
            if (x < 5 && room[y][x + 1])
                ++x;
            break;
        default:
            std::cerr << "invalid direction '" << d << "'";
            exit(EXIT_FAILURE);
        }

        result += x + y;
    }

    std::cout << result << '\n';

    exit(EXIT_SUCCESS);
}
