
#include <filesystem>
#include <exception>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <filesystem>

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
};

