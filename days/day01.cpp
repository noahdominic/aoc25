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
    int current_pos, zero_counter, rollover;

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
    }

    return zero_counter;
}

int
day01_part2()
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

        // We count how many times the position reaches 0 in `delta` steps.
        // Conceptually: delta = k0 + a * MAX_VALUE + remainder
        //   - k0: first step that hits 0
        //   - a: full cycles after first hit
        //   - remainder: leftover steps that don't reach 0 (ignored)
        // Of course, the above only makes sense when k0 > delta, otherwise
        // no zero is reached, so zero_counter is not incremented.
        int k0;

        if (data[i][0] == 'L') {
            k0 = current_pos;
        } else {
            k0 = MAX_VALUE - current_pos;
        }

        if (k0 == 0) k0 = MAX_VALUE;

        if (abs(delta) >= k0) {
            zero_counter += 1 + (abs(delta) - k0) / MAX_VALUE; // 1 initial zero count after k0 which is also reason why we subtract k0 from delta.
        }

        current_pos += delta;
        current_pos = (((current_pos % MAX_VALUE) + MAX_VALUE) % MAX_VALUE);
        }

    return zero_counter;
}