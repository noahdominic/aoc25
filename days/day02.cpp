#include <algorithm>
#include <cmath>
#include <string>
#include <vector>
#include <iostream>
#include "utils.hpp"

long repeat_number(long x, int k) {
    std::string s = std::to_string(x); // convert x to string
    std::string repeated;

    // Repeat the string k times
    for (int i = 0; i < k; ++i) {
        repeated += s;
    }

    // Convert back to long
    return std::stol(repeated);
}

long
day02_part1()
{
    std::vector<std::string> data = utils::read_file("input/day02.txt");
    long total = 0;

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
    std::vector<std::string> data = utils::read_file("input/day02.txt");
    long total = 0;

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
                // The concept here is simple.   We simply generalise the initial split from 2
                // to until the divisor becomes too large (I define it as the moment string 
                // length divided by the split (ie the divisor) becomes less than 1.0; a
                // few seconds of thought might convince you of that limit.)   Most of the
                // solution from part 1 remains unchanged.
                //
                // We prevent multiple counts by using a vector of already-checked numbers.
                // This is to avoid, for example, `222222222222` being counted 
                // several times as `222222` twice, `2222` thrice, `222` four times,
                // `22` six times, and `2` twelve times.
                long divisor = 2;
                std::vector<long> checked; 
                while (len / divisor >= 1.)
                {
                    if (len % divisor != 0){
                        divisor++;
                        continue;   // must be even
                    }

                    long halfLen = len / divisor;

                    long start = std::pow(10, halfLen - 1); // If, for example 123456, -> 100
                    long end   = std::pow(10, halfLen) - 1; // If, for example 123456, -> 999

                    for (long x = start; x <= end; ++x)
                    {
                        // Multiply x by 10^some k to "shift" it left, then add x to concatenate.
                        // Basically number(string(x) + string(x))
                        long n = repeat_number(x, divisor);

                        if (n < lLeft)
                        {
                            continue; // TODO.   any way to move this closer to lower limit?
                        }
                        if (n > lRight)
                        {
                            break; // monotonic, safe to stop
                        }

                        if (std::find(checked.begin(), checked.end(), n) == checked.end())
                        {
                            total += n;
                            checked.push_back(n);
                        }

                        std::cout << n << std::endl;
                    }

                    divisor++;
                }
            }
        }
    }

    return total;
}
