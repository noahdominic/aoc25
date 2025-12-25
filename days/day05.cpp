#include <algorithm>
#include <string>
#include <vector>
#include <optional>
#include <iostream>
#include "utils.hpp"

enum
state
{
    READING_RANGES,
    READING_INGREDIENTS
};

class Range {
public:
    long lower;
    long upper;

    // We're assuming in good faith that lower is always smaller/equal-to upper
    Range(long lower_, long upper_)
        : lower(lower_),
          upper(upper_) {}

    bool
    has_item(long n) const
    {
        return n >= lower && n <= upper;
    }

    long
    size() const
    {
        return upper - lower + 1;
    }

    static std::optional<Range>
    merge(const Range& r1, const Range& r2)
    {
        if (r1.upper < r2.lower || r2.upper < r1.lower) {
            return std::nullopt;
        }

        return Range(
            std::min(r1.lower, r2.lower),
            std::max(r1.upper, r2.upper)
        );
    }

    // -----------------------
    // Iterator support
    // -----------------------
    class
    iterator
    {
        long current;
    public:
        explicit iterator(long start) : current(start) {}
        long operator*() const { return current; }
        iterator& operator++() { ++current; return *this; }
        bool operator!=(const iterator& other) const { return current != other.current; }
    };

    iterator begin() const { return iterator(lower); }
    iterator end() const { return iterator(upper + 1); }  // +1 because 
};

std::vector<Range>
compress_ranges(std::vector<Range> ranges)
{
    if (ranges.empty())
        return {};

    // Sort ranges by lower bound
    std::sort(ranges.begin(), ranges.end(),
              [](const Range& a, const Range& b) { return a.lower < b.lower; });

    std::vector<Range> result;
    result.push_back(ranges[0]);

    for (int i = 1; i < ranges.size(); ++i)
    {
        auto merged = Range::merge(result.back(), ranges[i]);
        if (merged) {
            // Merge overlapping ranges
            result.back() = *merged;
        } else {
            // No overlap, add as new range
            result.push_back(ranges[i]);
        }
    }

    return result;
}

long
day05_part1()
{
    std::vector<std::string> data = utils::read_file("input/day05.txt");
    std::vector<Range> ranges;
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
            ranges.push_back(Range{std::stol(range_data[0]), std::stol(range_data[1])});
            
            std::cout<<line<<std::endl;
        } else if (state == READING_INGREDIENTS)
        {
            ingredients.push_back(std::stol(line));
        }
    }

    std::vector<Range> new_ranges = compress_ranges(ranges);

    for (float ingredient : ingredients)
    {
        bool is_fresh = false;

        for (Range range : ranges)
        {
            is_fresh = range.has_item(ingredient) || is_fresh;
        }

        if (is_fresh)
        {
            ++fresh_count;
        }
    }
   
    return fresh_count;
}

long
day05_part2()
{
    std::vector<std::string> data = utils::read_file("input/day05.txt");
    std::vector<Range> ranges;

    long total = 0;

    for (std::string line : data)
    {        
        std::vector<std::string> range_data = utils::split(line, "-");
            
        if (line.empty())
        {
            break;
        }
        
        // We're ASSUMING here that `range_data` only decomposes to two elements.
        ranges.push_back(Range{std::stol(range_data[0]), std::stol(range_data[1])});
        
        std::cout<<line<<std::endl;
    }

    std::vector<Range> new_ranges = compress_ranges(ranges);

    for (Range range : new_ranges)
    {
        total += range.size();
    }
    
    return total;
}