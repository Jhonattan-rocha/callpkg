// filemanager.h

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <fstream>
#include <vector>
#include <filesystem>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class FileManager {
public:
    FileManager();
    FileManager(const std::string& path, std::ios_base::openmode mode);
    ~FileManager();
    bool is_open();
    void open(const std::string& path, std::ios_base::openmode modo);
    void write(const std::string& data);
    void destroy();
    std::string read();
    std::vector<char> readBytes();
    void close();
    void writeJson(const json& data);
    json readJson();
private:
    std::fstream file;
    std::string file_path;
};

#endif
