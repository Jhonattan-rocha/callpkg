// filemanager.h
#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <fstream>
#include <iostream>
#include <vector>
#include <filesystem>

struct Open {
    std::fstream arquivo;
    std::string file_path;
    void open(const std::string& nomeArquivo, std::ios_base::openmode modo);
    void write(const std::string& conteudo);
    void destroy();
    std::string read();
    std::vector<char> readBytes();
    void close();
};

class FileManager {
public:
    FileManager(const std::string& path, std::ios_base::openmode mode);
    FileManager(const FileManager& other) = delete;  // Desabilitar cópia
    FileManager& operator=(const FileManager& other) = delete;  // Desabilitar cópia
    FileManager(FileManager&& other) noexcept;  // Construtor de movimento
    FileManager& operator=(FileManager&& other) noexcept;  // Operador de atribuição de movimento
    ~FileManager();
private:
    std::string path;
    Open file;
};

#endif // FILEMANAGER_H
