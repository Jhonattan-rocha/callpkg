#ifndef STRINGTOOLS_INL
#define STRINGTOOLS_INL

#include "StringTools.h"

template<typename T>
std::string StringTools::format_string(const std::string& format_str, std::vector<T>& vec) {
    std::string result = format_str;
    size_t pos = 0;
    while ((pos = result.find("{}")) != std::string::npos) {
        result.replace(pos, 2, std::format("{}", vec.front()));
        vec.erase(vec.begin());
    }
    return result;
}

#endif
