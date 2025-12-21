// #include "day01.hpp"
#include "utils.hpp"
#include <iostream>

int main(int argc, char** argv)
{
    // int day = std::stoi(argv[1]);
    // int part = std::stoi(argv[2]);

    std::vector<std::string> test_data = utils::read_file("input/day01-small.txt");

    std::cout << "Hello" << std::endl;

    for (uint i = 0; i < test_data.size(); ++i) {
        std::cout << test_data[i] << std::endl;
    }

    return 0;
}