// filemanager.cpp
#include "filemanager.h"

void Open::destroy(){
    if (arquivo.is_open()) {
        arquivo.close();
    }

    if (!arquivo.is_open()) {
        if (std::filesystem::exists(file_path)) {
            std::filesystem::remove(file_path);

            if (std::filesystem::exists(file_path)) {
                throw std::ios_base::failure("Erro ao deletar o arquivo.");
            }
        }
    }
}

void Open::open(const std::string& nomeArquivo, std::ios_base::openmode modo) {
    arquivo.open(nomeArquivo, modo);
    this->file_path = nomeArquivo;
    if (!arquivo.is_open()) {
        throw std::ios_base::failure("Erro ao abrir o arquivo.");
    }
}

void Open::write(const std::string& conteudo) {
    if (arquivo.is_open()) {
        arquivo << conteudo;
    } else {
        throw std::ios_base::failure("Erro ao escrever no arquivo.");
    }
}

std::string Open::read() {
    std::string conteudo;
    if (arquivo.is_open()) {
        arquivo.seekg(0, std::ios::end);
        conteudo.reserve(arquivo.tellg());
        arquivo.seekg(0, std::ios::beg);
        conteudo.assign((std::istreambuf_iterator<char>(arquivo)),
                        std::istreambuf_iterator<char>());
    } else {
        throw std::ios_base::failure("Erro ao ler o arquivo.");
    }
    return conteudo;
}

std::vector<char> Open::readBytes() {
    std::vector<char> bytes;
    if (arquivo.is_open()) {
        arquivo.seekg(0, std::ios::end);
        bytes.reserve(arquivo.tellg());
        arquivo.seekg(0, std::ios::beg);
        bytes.assign((std::istreambuf_iterator<char>(arquivo)),
                     std::istreambuf_iterator<char>());
    } else {
        throw std::ios_base::failure("Erro ao ler o arquivo.");
    }
    return bytes;
}

void Open::close() {
    if (arquivo.is_open()) {
        arquivo.close();
    }
}

FileManager::FileManager(const std::string& path, std::ios_base::openmode mode)
    : path(path), file() {
    auto fileMode = (mode & std::ios::out) ? std::ofstream::out : std::ifstream::in;
    file.open(path, fileMode);
}

FileManager::FileManager(FileManager&& other) noexcept
    : path(std::move(other.path)), file(std::move(other.file)) {
    other.path.clear();
}

FileManager& FileManager::operator=(FileManager&& other) noexcept {
    if (this != &other) {
        path = std::move(other.path);
        file = std::move(other.file);
        other.path.clear();
    }
    return *this;
}

FileManager::~FileManager() {
    file.close();
}
