// filemanager.cpp
#include "filemanager.h"

void FileManager::destroy(){
    if (file.is_open()) {
        file.close();
    }

    if (!file.is_open()) {
        if (std::filesystem::exists(file_path)) {
            std::filesystem::remove(file_path);

            if (std::filesystem::exists(file_path)) {
                throw std::ios_base::failure("Erro ao deletar o arquivo.");
            }
        }
    }
}

void FileManager::open(const std::string& path, std::ios_base::openmode modo) {
    file.open(path, modo);
    this->file_path = path;
    if (!file.is_open()) {
        throw std::ios_base::failure("Erro ao abrir o arquivo.");
    }
}

void FileManager::write(const std::string& data) {
    if (file.is_open()) {
        file << data;
    } else {
        throw std::ios_base::failure("Erro ao escrever no arquivo.");
    }
}

std::string FileManager::read() {
    std::string conteudo;
    if (file.is_open()) {
        file.seekg(0, std::ios::end);
        conteudo.reserve(file.tellg());
        file.seekg(0, std::ios::beg);
        conteudo.assign((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    } else {
        throw std::ios_base::failure("Erro ao ler o arquivo.");
    }
    return conteudo;
}

std::vector<char> FileManager::readBytes() {
    std::vector<char> bytes;
    if (file.is_open()) {
        file.seekg(0, std::ios::end);
        bytes.reserve(file.tellg());
        file.seekg(0, std::ios::beg);
        bytes.assign((std::istreambuf_iterator<char>(file)),
                     std::istreambuf_iterator<char>());
    } else {
        throw std::ios_base::failure("Erro ao ler o arquivo.");
    }
    return bytes;
}

void FileManager::close() {
    if (file.is_open()) {
        file.close();
    }
}

FileManager::FileManager(const std::string& path, std::ios_base::openmode mode){
    file.open(path, mode);
}

FileManager::FileManager(){
}

FileManager::~FileManager() {
    file.close();
}
