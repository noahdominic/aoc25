#include <cmath>
#include <string>
#include <vector>
#include <iostream>
#include "utils.hpp"

// The 'knob' doesn't go above 99 and loops back to 0
#define MAX_VALUE 100

// This is declared in the problem description as the starting position.
#define INITIAL_POS 50


int
day01_part1()
{
    int current_pos, zero_counter;

    current_pos = INITIAL_POS;
    zero_counter = 0;

    std::vector<std::string> data = utils::read_file("input/day01.txt");

    for (uint i = 0; i < data.size(); ++i) {
        int delta = std::stoi(data[i].substr(1));

        if (data[i][0] == 'L') {
            delta *= -1;
        }

        current_pos += delta;

        // The below calculates the positive modulo out of the negative, which
        // is the default in C++.   For more info, check out
        // https://en.wikipedia.org/wiki/Modulo
        current_pos = ((current_pos % MAX_VALUE) + MAX_VALUE) % MAX_VALUE; 

        if (current_pos == 0) {
            ++zero_counter;
        }
    }

    return zero_counter;
}

int
day01_part2()
{
    return 0;
}