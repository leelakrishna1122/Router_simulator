#include "util.h"
#include <sstream>

namespace util {
    std::vector<std::string> split(const std::string &line) {
        std::vector<std::string> tokens;
        std::stringstream ss(line);
        std::string word;
        while (ss >> word) {
            tokens.push_back(word);
        }
        return tokens;
    }
}
