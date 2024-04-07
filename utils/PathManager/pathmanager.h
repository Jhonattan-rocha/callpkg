#ifndef PATHMANAGER_H
#define PATHMANAGER_H

#include <filesystem>
#include <exception>
#include <Logging/logging.h>
#include <string>
#include <vector>
#include <utility>

#ifdef _WIN32
const char PATH_SEPARATOR = '\\';
#elif __linux__
const char PATH_SEPARATOR = '/';
#endif

struct FileInfo {
    std::string type;
    std::string name;
    std::string path;
    std::uintmax_t size;
    std::filesystem::file_time_type lastModified;
};

class PathManager
{
public:
    PathManager();
public:
    std::string getMainPath();
    std::vector<FileInfo> listDir(const std::wstring& path);
    std::string getUserName();
    void createDirectory(const std::string& full_path, const bool force);
    void delDirectory(const std::string& full_path);
    bool exists(const std::string& path);
    std::string join_paths(const std::vector<std::string>& components);
};

#endif
