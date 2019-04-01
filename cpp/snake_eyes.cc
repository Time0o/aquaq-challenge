#include <algorithm>
#include <cassert>
#include <iostream>


static struct Die {
    Die(int front, int left, int top) : front(front), left(left), top(top) {}

    void turn(char dir) {
        int front_old = front;

        switch (dir) {
        case 'U':
            front = 7 - top;
            top = front_old;
            break;
        case 'D':
            front = top;
            top = 7 - front_old;
            break;
        case 'L':
            front = 7 - left;
            left = front_old;
            break;
        case 'R':
            front = left;
            left = 7 - front_old;
            break;
        default:
            assert(false);
        }
    }

    int front, left, top;

} die1(1, 2, 3), die2(1, 3, 2);


int main()
{
    std::string directions;
    std::cin >> directions;

    int result = 0;

    char dir;
    for (auto i = 0u; i < directions.length(); ++i) {
        dir = directions[i];
        die1.turn(dir);
        die2.turn(dir);

        if (die1.front == die2.front)
            result += i;
    }

    std::cout << result << '\n';

    exit(EXIT_SUCCESS);
}
