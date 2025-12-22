#include <vector>
#include <string>
#include <iostream>
#include "utils.hpp"

int    
day03_part1()
{
    std::vector<std::string> data = utils::read_file("input/day03.txt");
    int total = 0;

    for (std::string line : data) {
        std::cout << line << std::endl;
        int left, right;

        for (int search_digit = 9 ; search_digit >= 0; --search_digit)
        {
            for (int i = 0; i < line.length() - 1; ++i)
            {
                if (line[i] - '0' == search_digit)
                {
                    for (int search_digit_right = 9; search_digit_right >= 0; --search_digit_right)
                    {
                        for (int j = i + 1; j < line.length(); ++j) 
                        {
                            if (line[j] - '0' == search_digit_right)
                            {
                                left = search_digit;
                                right = search_digit_right;
                                total += left*10 + right;
                                goto proceed_to_next_line;
                            }
                        }
                    }
                }
            }
        }
proceed_to_next_line:
    }
    return total;
}


int
day03_part2()
{
    std::vector<std::string> data = utils::read_file("input/day03-small.txt");
    int total = 0;
    // int n = 12; // for example, generalise to 3 digits

    // for (const std::string &line : data) {
    //     std::vector<int> digits = find_digits(line, n);
    //     int value = 0;
    //     for (int d : digits) {
    //         value = value * 10 + d;
    //     }
    //     total += value;
    // }

    return total;
}
