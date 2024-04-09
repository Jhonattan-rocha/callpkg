#include "pathmanager.h"

#ifdef _WIN32
#include <windows.h>
#endif

namespace fs = std::filesystem;

PathManager::PathManager() {
    #if _WIN32
    CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    #endif
}

std::string PathManager::getUserName(){
    #if _WIN32
    const DWORD buffer_size = 256;
    char username[buffer_size];
    DWORD size = buffer_size;

    if (GetUserNameA(username, &size)) {
        //tirar isso para a versão final, pequeno ajuste para arrumar um problema do meu pc em questão
        std::string usr = username;
        size_t pos = usr.find("o");
        usr.replace(pos, 1, "i");
        return usr;
    } else {
        return "";
    }
    #endif
}

std::string PathManager::getMainPath(){
    #ifdef _WIN32
        return "C:\\Users\\" + this->getUserName();
    #elif __linux__
        return "/home/" + this->getUserName();
    #endif
}

std::vector<FileInfo> PathManager::listDir(const std::wstring& path) {
    std::vector<FileInfo> files_directories;

    for (const auto& entry : fs::directory_iterator(path)) {
        FileInfo info;
        info.path = entry.path().string();
        info.name = entry.path().filename().string();
        if (fs::is_directory(entry.path())) {
            info.type = "D";
        } else {
            info.type = "F";
            info.size = fs::file_size(entry.path());
        }
        info.lastModified = fs::last_write_time(entry.path());
        files_directories.push_back(info);
    }

    return files_directories;
}

void PathManager::createDirectory(const std::string& full_path, const bool force){
    if(!force && fs::exists(full_path)){
        throw std::ios_base::failure("Diretório já existe");
    }
    fs::create_directories(full_path);
}

void PathManager::delDirectory(const std::string& full_path){
    fs::path path = full_path;

    if(!fs::exists(path)){
        throw std::runtime_error("Diretório não existe");
    }

    for(const auto& entry : fs::directory_iterator(path)){
        if(entry.is_directory()){
            delDirectory(entry.path().string());
        }else{
            fs::remove(entry.path());
        }
    }

    try {
        fs::remove(path);
    } catch (const std::exception& e) {
        // Handle exception or log the error if necessary
        LOGERR("Erro ao remover diretório " + path.string() + ": " + e.what());
    }
}

bool PathManager::exists(const std::string& path){
    return fs::exists(path);
}

std::string PathManager::join_paths(const std::vector<std::string>& components) {
    std::string path;
    for (const auto& component : components) {
        // Adiciona uma barra (ou outro caractere) apenas se a string não estiver vazia
        if (!path.empty() && path.back() != PATH_SEPARATOR) {
            path += PATH_SEPARATOR;
        }
        path += component;
    }
    return path;
}

std::vector<std::string> PathManager::hasPath(const std::vector<std::string>& args) {
    std::vector<std::string> response;
    StringTools st;

    for(const auto& path : args){
        std::string str = st.strip(path);
        if(fs::exists(str)){
            response.push_back(str);
        }
    }

    return response;
}
