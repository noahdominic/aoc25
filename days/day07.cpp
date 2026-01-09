#include <string>
#include <vector>
#include <iostream>
#include <bitset>
#include <algorithm>
#include "utils.hpp"
#include <set>

#define EMPTY_SPACE '.'
#define SOURCE 'S'
#define SPLITTER '^'
#define LIGHT '|'

long
day07_part1()
{
    std::vector<std::string> data = utils::read_file("input/day07.txt");
    std::set<size_t> light_idxs;

    // Find the initial source position
    const size_t source_pos = data[0].find(SOURCE);
    if (source_pos != std::string::npos) {
        light_idxs.insert(source_pos);
    }

    long splitter_count = 0;

    for (size_t scan_idx = 1; scan_idx < data.size(); ++scan_idx) {
        std::set<size_t> splitter_idxs;

        // Identify splitter positions in the current row
        for (size_t light_idx : light_idxs) {
            if (data[scan_idx][light_idx] == SPLITTER) {
                splitter_idxs.insert(light_idx);
            }
        }

        // Process splitters
        for (size_t splitter_idx : splitter_idxs) {
            if (light_idxs.count(splitter_idx)) {
                ++splitter_count;

                // Insert new light positions if within bounds
                if (splitter_idx > 0) {
                    light_idxs.insert(splitter_idx - 1);
                }
                if (splitter_idx + 1 < data[0].size()) {
                    light_idxs.insert(splitter_idx + 1);
                }

                light_idxs.erase(splitter_idx);
            }
        }
    }

    return splitter_count;
}

long
day07_part2()
{
    return 0;
}