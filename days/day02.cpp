#include <cmath>
#include <string>
#include <vector>
#include <iostream>
#include "utils.hpp"

long
day02_part1()
{
    std::vector<std::string> data = utils::read_file("input/day02.txt");
    long total = 0;
    
    // return brute_force_sum(data);

    for (std::string& line : data)
    {
        std::vector<std::string> ranges = utils::split(line, ",");

        for (std::string& range : ranges)
        {
            // In case of empty strings
            if (range.empty())
            {
                continue;
            }

            // SHOULD be size 2, ie a pair
            std::vector<std::string> values = utils::split(range, "-");

            long lLeft = std::stoll(values[0]);
            long lRight = std::stoll(values[1]);

            // Let's generate "invalid" values then check if they're within the range.
            // For example, we have range 1212-1216.
            // We SHOULD generate 1010, 1111, 1212, 1313, 1414, ..., 9999
            // then check if those "invalid" values are in range,
            // EXCEPT, we stop generating immediately when the generated number
            // exceeds the maximum/right value
            long lenL = values[0].size();
            long lenR = values[1].size();

            for (long len = lenL; len <= lenR; ++len)
            {
                if (len % 2 != 0){
                    continue;   // must be even
                }

                long halfLen = len / 2;

                long start = std::pow(10, halfLen - 1); // If, for example 123456, -> 100
                long end   = std::pow(10, halfLen) - 1; // If, for example 123456, -> 999

                for (long x = start; x <= end; ++x)
                {
                    // Multiply x by 10^some k to "shift" it left, then add x to concatenate.
                    // Basically number(string(x) + string(x))
                    long n = x * pow(10, (int)log10(x) + 1) + x;

                    if (n < lLeft)
                    {
                        continue; // TODO.   any way to move this closer to lower limit?
                    }
                    if (n > lRight)
                    {
                        break; // monotonic, safe to stop
                    }

                    total += n;
                }
            }
        }
    }

    return total;
}

long
day02_part2()
{
    return 0;
}
