#include "day04.hpp"
#include "utils.hpp"
#include <iostream>
#include <string>
#include <vector>

int count_existing_neighbours(std::vector<std::string>& data, int i, int j) {
    int count = 0;

    for (int di = -1; di <= 1; ++di) {
        for (int dj = -1; dj <= 1; ++dj) {
            if (di == 0 && dj == 0)
                continue;

            int ni = i + di;
            int nj = j + dj;

            if (ni >= 0 && ni < data.size() && nj >= 0 && nj < data[0].size() &&
                data[ni][nj] == '@')
                ++count;
        }
    }

    return count;
}

int day04_part1() {
    std::vector<std::string> data = utils::read_file("input/day04.txt");
    int count = 0;

    for (int i = 0; i < data.size(); ++i) {
        for (int j = 0; j < data[i].size(); ++j) {
            if (count_existing_neighbours(data, i, j) < 4 && data[i][j] == '@')
                ++count;
        }
    }

    return count;
}

int day04_part2() {
    std::vector<std::string> data = utils::read_file("input/day04.txt");
    std::vector<std::string> data_clone = data; // is clone, not an assignment

    int count_removable, count_removable_total = 0;

    do {
        count_removable = 0; // reset
        for (int i = 0; i < data.size(); ++i) {
            for (int j = 0; j < data[i].size(); ++j) {
                if (count_existing_neighbours(data, i, j) < 4 &&
                    data[i][j] == '@') {
                    data_clone[i][j] = 'x';
                    ++count_removable;
                    ++count_removable_total;
                }
            }
        }
        data = data_clone;
    } while (count_removable > 0);

    return count_removable_total;
}