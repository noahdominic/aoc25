#pragma once

#include <string>
#include <vector>

namespace utils
{
    std::vector<std::string> read_file(std::string file_path);
    std::vector<std::string> split(std::string s, std::string delimiter);
    std::vector<std::string> split_skip_empty(const std::string& s, const std::string& delimiter);
}
