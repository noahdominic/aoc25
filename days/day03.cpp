#include <vector>
#include <string>
#include "utils.hpp"

#define PART2_LEVEL 12

int    
day03_part1()
{
    std::vector<std::string> data = utils::read_file("input/day03.txt");
    int total = 0;

    for (std::string line : data) {
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

/// @brief This is a generalised version of the loop above.
/// @param line 
/// @param pos Starting position of search domain
/// @param depth The number of digits we've search so far
/// @param n Max depth; The number of 'batteries' necessary to be on
/// @param digits This is the max "number" we expect. This is filled as the loop continues
/// @return 
bool find_digits(
    const std::string& line,
    int pos,
    int depth,
    int num_of_batteries,
    std::vector<int>& digits
) {
    if (depth == num_of_batteries)
        return true;

    for (int d = 9; d >= 0; --d)
    {
        // Re:Upper search limit.
        //
        // Notice how in the 2 digit case, the upper level has domain of length - 1 and the lower
        // level has length.   This is for safety purposes (I encountered them earlier, though
        // I can't seem to re-create it any more.   This safety "barrier" seems to be generalizable to:
        //
        //         num of batteries - current depth - 1
        //
        // For sanity check: at the first part, at depth=0, number of batteries=2
        //         2 - 0 - 1    -->    1  (meaning we leave 1 digit)
        // and given a situation like this:
        //         XXXXXXXXXXXXXXX
        // the search domain for the first level is:
        //         ++++++++++++++X
        //
        // Then at the second level at depth=1, 
        //         2 - 1 - 1    -->    0  (meaning last item is included in search domain)
        // with the search domainS (plural) being like this:
        //         X++++++++++++++ (if a 'good' number if found at index 0)
        //         XX+++++++++++++ (if a 'good' number if found at index 1)
        //
        // This constraint prevents out-of-range searches and guarantees that
        // deeper recursive calls can still succeed.   (NOTE: In my case, I DIDN'T have to do it,
        // but like I said, I encountered a similar error.  So better safe than sorry.)
        for (int i = pos; i < line.length() - (num_of_batteries - depth - 1); ++i)
        {
            if (line[i] - '0' == d)
            {
                digits[depth] = d;
                if (find_digits(line, i + 1, depth + 1, num_of_batteries, digits))
                {
                    return true;
                }
            }
        }
    }
    return false;
}


long
day03_part2()
{
    std::vector<std::string> data = utils::read_file("input/day03.txt");
    long total = 0;

    for (auto line : data) 
    {

        std::vector<int> digits(PART2_LEVEL);
        
        if (find_digits(line, 0, 0, PART2_LEVEL, digits)) {
            long joltage_of_line = 0;
            for (int d : digits)
            {
                joltage_of_line = joltage_of_line * 10 + d;
            }
            total += joltage_of_line;
        }
    }
    return total;
}
