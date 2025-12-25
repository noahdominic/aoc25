#include <string>
#include <vector>
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
        
        total += column_result;
    }

    return total;
}

std::string
extract_column(const std::vector<std::string>& data, size_t col)
{
    std::string result;
    result.reserve(data.size());

    for (const std::string& str : data) {
        if (col < str.size()) {
            result += str[col];
        }
    }

    return result;
}

std::vector<long>
extract_operands(std::vector<std::string>& data,
    size_t col,
    int offset)
{
    std::vector<long> operands({});

    while (offset >= 0)
    {
        operands.emplace_back(std::stol(extract_column(data, col + offset)));
        --offset;
    }

    return operands;
}

long
day06_part2()
{
    long total = 0;
    std::vector<std::string> data = utils::read_file("input/day06.txt");
    std::string last_row = data.back();
    data.pop_back(); // important, so we can do loops on data w/o having to worry abt the last row
    std::vector<operation> operations({last_row[0] == '+' ? ADD : MULTIPLY});
    std::vector<size_t> operation_locations({0});
    std::vector<size_t> operation_offsets;

    // Skip first item; it's been done above at declaration
    for (size_t i = 1; i < last_row.size(); ++i)
    {
        if (last_row[i] != ' ')
        {
            operations.push_back(last_row[i] == '+' ? ADD : MULTIPLY);
            operation_locations.push_back(i);
        }
    }
    
    // Should check if more than 1 item but realistically don't have to
    // From start to penultimate since we're doing index + 1
    for (size_t i = 0; i + 1 < operation_locations.size(); ++i)
    {
        operation_offsets.push_back(operation_locations[i + 1] - operation_locations[i] - 2);
    }

    // Last item
    operation_offsets.push_back(last_row.size() - operation_locations.back() - 1);

    for (size_t current_op_index = 0; current_op_index < operation_locations.size(); ++current_op_index)
    {
        // Operands are numbers to be operated
        std::vector<long> operands = extract_operands(data, operation_locations[current_op_index], operation_offsets[current_op_index]);

        // Should check if operands are not empty but don't have to realistically
        long sub_total = operands[0];
        for (size_t i = 1; i < operands.size(); ++i)
        {
            sub_total = (operations[current_op_index] == ADD) ? sub_total + operands[i] : sub_total * operands[i];
        }

        total += sub_total;

    }

    return total;
}
