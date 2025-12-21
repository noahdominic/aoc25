#include <fstream>
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
}
