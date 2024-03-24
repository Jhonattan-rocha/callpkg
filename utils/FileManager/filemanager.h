// filemanager.h
#include <fstream>
#include <iostream>
#include <vector>
#include <filesystem>

class FileManager {
public:
    FileManager();
    FileManager(const std::string& path, std::ios_base::openmode mode);
    ~FileManager();
    void open(const std::string& path, std::ios_base::openmode modo);
    void write(const std::string& data);
    void destroy();
    std::string read();
    std::vector<char> readBytes();
    void close();
private:
    std::fstream file;
    std::string file_path;
};
