#pragma once

#include <ostream>
#include <string>
#include <vector>

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
    os << "[";
    for (std::size_t i = 0; i < v.size(); ++i) {
        os << v[i];
        if (i + 1 < v.size())
            os << ", ";
    }
    os << "]";
    return os;
}

namespace utils {
std::vector<std::string> read_file(std::string file_path);
std::vector<std::string> split(std::string s, std::string delimiter);
std::vector<std::string> split_skip_empty(const std::string& s,
                                          const std::string& delimiter);
} // namespace utils
