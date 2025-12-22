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

    /// split
    ///
    /// by Arafat Hasan, edited by Quonux
    /// https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
    ///
    /// Split string based on a string delimiter. Such as splitting string "adsf-+qwret-+nvfkbdsj-+orthdfjgh-+dfjrleih" based on string delimiter "-+", output will be {"adsf", "qwret", "nvfkbdsj", "orthdfjgh", "dfjrleih"}
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
}
