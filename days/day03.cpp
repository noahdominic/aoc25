#include "utils.hpp"
#include <iostream>
#include <string>
#include <vector>

#define PART2_LEVEL 12

int day03_part1() {
    std::vector<std::string> data = utils::read_file("input/day03.txt");
    int total = 0;

    for (std::string line : data) {
        char left = 0;
        size_t left_pos = 0;
        char right = 0;

        for (size_t i = 0; i < line.length() - 1; ++i) {
            if (line[i] > left) {
                left = line[i];
                left_pos = i;
            }
        }

        for (size_t i = left_pos + 1; i < line.length(); ++i) {
            if (line[i] > right) {
                right = line[i];
            }
        }

        std::cout << left << right << std::endl;

        total += (left - '0') * 10 + (right - '0');
    }
    return total;
}

/// @brief This is a generalised version of the loop above.
/// @param line
/// @param pos Starting position of search domain
/// @param depth The number of digits we've search so far
/// @param n Max depth; The number of 'batteries' necessary to be on
/// @param digits This is the max "number" we expect. This is filled as the loop
/// continues
/// @return
bool find_digits(const std::string& line, int pos, int depth,
                 int num_of_batteries, std::vector<int>& digits) {
    if (depth == num_of_batteries)
        return true;

    // Re: Search domains
    //
    // The search process here is simple.   Let's assume length of 10 is split
    // into 2.
    //     xxxxxxxxxx
    // For the first digit, we'll search from the first index to second to the
    // last.
    //     +++++++++x (first digit search domain)
    // After which the second digit is search from the position of the max to
    // the last.
    //     xxx+++++++
    //       ^
    //       ^
    //       We assume that the max first digit is here.
    //
    // This can be generalised into higher splits by minimising the search
    // domain. The key insight: we must reserve space for the remaining digits.
    // If we need to extract 'k' more digits after the current one, we must stop
    // our search 'k' positions before the end to ensure enough characters
    // remain.
    //
    // Example: 3 batteries, string "4817293650" (length 10)
    //
    // Depth 0 (finding 1st digit):
    //   Need to reserve 2 positions for digits 2 and 3
    //   Search domain: indices 0-7
    //
    //   4 8 1 7 2 9 3 6 5 0
    //   + + + + + + + + - -   (+ = search, - = reserved)
    //   |-------------|
    //     Find max='9' at position 5
    //
    // Depth 1 (finding 2nd digit):
    //   Start from position 6 (after the '9')
    //   Need to reserve 1 position for digit 3
    //   Search domain: indices 6-8
    //
    //   4 8 1 7 2 9 3 6 5 0
    //   - - - - - - + + + -   (start at pos 6)
    //               |---|
    //     Find max='6' at position 7
    //
    // Depth 2 (finding 3rd digit):
    //   Start from position 8 (after the '6')
    //   Need to reserve 0 positions
    //   Search domain: indices 8-9
    //
    //   4 8 1 7 2 9 3 6 5 0
    //   - - - - - - - - + +   (start at pos 8)
    //                   |-|
    //     Find max='5' at position 8
    //
    // Result: digits = [9, 6, 5] (the maximum number from 3 non-overlapping
    // digits)
    //
    // The loop bound: i < line.length() - (num_of_batteries - depth - 1)
    //   - num_of_batteries - depth = total digits still needed (including
    //   current)
    //   - num_of_batteries - depth - 1 = digits needed AFTER current digit
    //   - This ensures we leave enough characters for subsequent recursive
    //   calls

    char max = '0';
    int max_pos = 0;
    for (int i = pos; i < line.length() - (num_of_batteries - depth - 1); ++i) {
        if (line[i] > max) {
            max = line[i];
            max_pos = i;
        }
    }

    digits[depth] = max - '0';
    if (find_digits(line, max_pos + 1, depth + 1, num_of_batteries, digits)) {
        return true;
    }
    return false;
}

long day03_part2() {
    std::vector<std::string> data = utils::read_file("input/day03.txt");
    long total = 0;

    for (auto line : data) {

        std::vector<int> digits(PART2_LEVEL);

        if (find_digits(line, 0, 0, PART2_LEVEL, digits)) {
            long joltage_of_line = 0;
            for (int d : digits) {
                joltage_of_line = joltage_of_line * 10 + d;
            }
            total += joltage_of_line;
        }
    }
    return total;
}
