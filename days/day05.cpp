#include <string>
#include <vector>
#include <iostream>
#include "utils.hpp"

enum state{
    READING_RANGES,
    READING_INGREDIENTS
};

long
day05_part1()
{
    std::vector<std::string> data = utils::read_file("input/day05-small.txt");
    std::vector<std::vector<long>> ranges;
    std::vector<long> ingredients;

    int state = READING_RANGES;
    
    long fresh_count = 0;

    for (std::string line : data)
    {        
        std::vector<std::string> range_data = utils::split(line, "-");
        if (state == READING_RANGES)
        {
            
            if (line.empty())
            {
                state = READING_INGREDIENTS;
                continue;
            }
            
            // We're ASSUMING here that `range_data` only decomposes to two elements.
            long lower_limit = std::stol(range_data[0]);
            long upper_limit = std::stol(range_data[1]);
            
            ranges.push_back({lower_limit, upper_limit});
            
            std::cout<<line<<std::endl;
        } else if (state == READING_INGREDIENTS)
        {
            ingredients.push_back(std::stol(line));
        }
    }

    for (float ingredient : ingredients)
    {
        bool is_fresh = false;

        for (std::vector<long> range : ranges)
        {
            is_fresh |= (ingredient >= range[0] && ingredient <= range[1]);
        }
    }
   

    return 0;
}