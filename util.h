#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>

namespace util {
    // Split a string by spaces and return tokens
    std::vector<std::string> split(const std::string &line);
}

#endif // UTIL_H
