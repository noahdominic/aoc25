#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace utils
{
    std::vector<std::string>
    read_file(std::string file_path)
    {
        std::ifstream file(file_path);
        std::vector<std::string> lines;
        std::string line;

        while (std::getline(file, line))
        {
            lines.push_back(line);
        }

        return lines;
    }

    /// @brief Splits a string using a delimiter, preserving empty tokens.
    ///
    /// This function divides the input string into substrings separated by
    /// the specified delimiter. Consecutive delimiters, as well as leading
    /// or trailing delimiters, result in empty strings in the returned vector.
    ///
    /// @param s
    ///     The input string to split.
    ///
    /// @param delimiter
    ///     The delimiter string used to separate tokens.
    ///
    /// @return
    ///     A vector of substrings extracted from the input string, including
    ///     empty strings for consecutive, leading, or trailing delimiters.
    ///
    /// @note
    ///     If the delimiter is empty, the behaviour is undefined and may
    ///     result in an infinite loop.
    ///
    /// @example
    ///     @code
    ///     split("one,two,,three", ",");
    ///     // Returns: {"one", "two", "", "three"}
    ///
    ///     split(",one,,two,", ",");
    ///     // Returns: {"", "one", "", "two", ""}
    ///     @endcode
    ///
    /// @author
    ///     by Arafat Hasan, edited by Quonux
    ///     https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
    std::vector<std::string>
    split(std::string s, std::string delimiter)
    {
        size_t pos_start = 0, pos_end, delim_len = delimiter.length();
        std::string token;
        std::vector<std::string> res;

        while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
            token = s.substr (pos_start, pos_end - pos_start);
            pos_start = pos_end + delim_len;
            res.push_back (token);
        }

        res.push_back (s.substr (pos_start));
        return res;
    }

    /// @brief Splits a string using a delimiter, skipping empty tokens.
    ///
    /// This function divides the input string into substrings separated by
    /// the specified delimiter. Consecutive delimiters, as well as leading
    /// or trailing delimiters, do not produce empty tokens in the result.
    ///
    /// @param s
    ///     The input string to split.
    ///
    /// @param delimiter
    ///     The delimiter string used to separate tokens.
    ///     Must not be empty.
    ///
    /// @return
    ///     A vector of non-empty substrings extracted from the input string.
    ///     If no non-empty tokens are found, the returned vector is empty.
    ///
    /// @note
    ///     If the delimiter is empty, the function returns an empty vector.
    ///
    /// @example
    ///     @code
    ///     split_skip_empty("one,two,,three", ",");
    ///     // Returns: {"one", "two", "three"}
    ///
    ///     split_skip_empty(",one,,two,", ",");
    ///     // Returns: {"one", "two"}
    ///     @endcode
    std::vector<std::string>
    split_skip_empty(const std::string& s, const std::string& delimiter)
    {
        if (delimiter.empty())
            return {};

        size_t pos_start = 0;
        size_t pos_end;
        const size_t delim_len = delimiter.length();

        std::vector<std::string> res;

        while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
            if (pos_end > pos_start) {
                res.emplace_back(s.substr(pos_start, pos_end - pos_start));
            }
            pos_start = pos_end + delim_len;
        }

        if (pos_start < s.length()) {
            res.emplace_back(s.substr(pos_start));
        }

        return res;
    }
}
