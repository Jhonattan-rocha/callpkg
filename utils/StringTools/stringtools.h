#ifndef STRINGTOOLS_H
#define STRINGTOOLS_H

#include <Logging/logging.h>
#include <string>
#include <utility>
#include <vector>
#include <iomanip>
#include <sstream>
#include <algorithm>

#if __cplusplus >= 202002L
#include <format>
#endif

class StringTools
{
public:
    StringTools();
    std::vector<std::string> split(const std::string& str, char delimiter);
    std::string join(std::vector<std::string> parts, char delimiter);
    std::string lstrip(const std::string& s);
    std::string rstrip(const std::string& s);
    std::string strip(const std::string& s);
    std::vector<size_t> find(const std::string& search, const std::string& str, const bool all);
    std::string limit_str(int limit, std::string value);
    std::string uppercase(const std::string& str);
    std::string lowercase(const std::string& str);
    int count(const std::string& str, const std::string& sub);
    template<typename... Args>
    std::string format_string(const std::string& format, Args&&... args);
    template<typename... Args>
    std::string format_string_std(const std::string& format, Args&&... args);
private:
    template<typename T>
    void format_helper(std::stringstream& ss, const std::string& format, size_t& pos, const T& arg);
    template<typename T, typename... Args>
    void format_helper(std::stringstream& ss, const std::string& format, size_t& pos, const T& arg, const Args&... args);
};

#include "stringtools.inl"

#endif
