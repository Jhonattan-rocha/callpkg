#ifndef STRINGTOOLS_INL
#define STRINGTOOLS_INL

#include "StringTools.h"

template<typename T>
void  StringTools::format_helper(std::stringstream& ss, const std::string& format, size_t& pos, const T& arg) {
    size_t open_brace = format.find('{', pos);
    size_t close_brace = format.find('}', pos);
    if (open_brace == std::string::npos || close_brace == std::string::npos || close_brace < open_brace) {
        ss << format.substr(pos);
        return;
    }
    ss << format.substr(pos, open_brace - pos);
    ss << arg;
    pos = close_brace + 1;
    format_helper(ss, format, pos, arg);
}

template<typename T, typename... Args>
void StringTools::format_helper(std::stringstream& ss, const std::string& format, size_t& pos, const T& arg, const Args&... args) {
    size_t open_brace = format.find('{', pos);
    size_t close_brace = format.find('}', pos);
    if (open_brace == std::string::npos || close_brace == std::string::npos || close_brace < open_brace) {
        ss << format.substr(pos);
        return;
    }
    ss << format.substr(pos, open_brace - pos);
    ss << arg;
    pos = close_brace + 1;
    format_helper(ss, format, pos, args...);
}

template<typename... Args>
std::string StringTools::format_string(const std::string& format, Args&&... args) {
    std::stringstream ss;
    size_t pos = 0;
    format_helper(ss, format, pos, std::forward<Args>(args)...);
    return ss.str();
}

template<typename... Args>
std::string StringTools::format_string_std(const std::string& format, Args&&... args) {
#if __cplusplus >= 202002L 
    return std::vformat(format, std::make_format_args(args...));
#else
    return format_string(format, std::forward<Args>(args)...);
#endif
}

#endif
