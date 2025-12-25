#include <string>
#include <vector>
#include <iostream>
#include "utils.hpp"

enum
operation
{
    ADD,
    MULTIPLY
};

long
day06_part1()
{
    std::vector<std::vector<long>> grid;
    std::vector<std::string> data = utils::read_file("input/day06.txt");
    
    // Parse all rows except the last into the grid
    for (size_t i = 0; i < data.size() - 1; ++i)
    {
        std::vector<std::string> tokens = utils::split_skip_empty(data[i], " ");
        std::vector<long> row;
        row.reserve(tokens.size());
        
        for (const std::string& token : tokens)
        {
            row.push_back(std::stol(token));
        }
        
        grid.push_back(std::move(row));
    }

    // Parse operations from the last line
    std::vector<operation> operations;
    for (const std::string& token : utils::split_skip_empty(data.back(), " "))
    {
        operations.push_back(token == "+" ? ADD : MULTIPLY);
    }

    // Apply operations column-wise and accumulate results
    long total = 0;
    for (size_t col = 0; col < operations.size(); ++col)
    {
        long column_result = grid[0][col];
        
        // NOTE: Assumes, there's more than one operand per line, which seems to be the case.
        for (size_t row = 1; row < grid.size(); ++row)
        {
            column_result = (operations[col] == ADD) 
                ? column_result + grid[row][col]
                : column_result * grid[row][col];
        }
        
        std::cout << "At column " << col << ", the total is: " << column_result << std::endl;
        total += column_result;
    }

    return total;
}

long
day06_part2()
{
    return 0;
}
