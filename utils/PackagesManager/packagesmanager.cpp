// packagesmanager.cpp

#include "packagesmanager.h"

PackagesManager::PackagesManager(){}

json PackagesManager::recover_informations(const std::string& name){
    FileManager fm("./packages.json", std::ios::in);
    StringTools st;
    json return_software_info = nullptr;
    json softwaresInfo = fm.readJson();
    fm.close();

    for (auto& software : softwaresInfo["Softwares"]) {
        std::string softwareName = software["software-name"];
        if(st.lowercase(softwareName) == st.lowercase(name)){
            return_software_info = software;
            break;
        }
    }

    return return_software_info;
}

void PackagesManager::save_informations(const json& info){
    try {
        FileManager fm_in("./packages.json", std::ios::in);
        if (!fm_in.is_open()) {
            std::cerr << "Erro ao abrir o arquivo para leitura." << std::endl;
            return;
        }
        
        json softwaresInfo = fm_in.readJson();
        fm_in.close();

        FileManager fm_out("./packages.json", std::ios::out);
        if (!fm_out.is_open()) {
            std::cerr << "Erro ao abrir o arquivo para escrita." << std::endl;
            return;
        }

        softwaresInfo["Softwares"].push_back(info);
        fm_out.writeJson(softwaresInfo);
        fm_out.close();
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

json PackagesManager::getTemplate(){
    FileManager fm_in("./packages-template.json", std::ios::in);
    if (!fm_in.is_open()) {
        std::cerr << "Erro ao abrir o arquivo para leitura." << std::endl;
        return nullptr;
    }
    json data = fm_in.readJson();
    if(data["Softwares"].size() != 1){
        std::cerr << "Erro com o arquivo template." << std::endl;
        return nullptr;
    }

    auto temp = data["Softwares"][0];

    return temp;
}

json PackagesManager::get_macro(const std::string& name){
    FileManager fm("./packages.json", std::ios::in);
    StringTools st;
    json return_macro_info = nullptr;
    json macrosInfos = fm.readJson();
    fm.close();

    for (auto& macro : macrosInfos["Macros"]) {
        std::string macroName = macro["name"];
        if(st.lowercase(macroName) == st.lowercase(name)){
            return_macro_info = macro;
            break;
        }
    }

    return return_macro_info;
}

void PackagesManager::save_macro(const json& macro){
    try {
        FileManager fm_in("./packages.json", std::ios::in);
        if (!fm_in.is_open()) {
            std::cerr << "Erro ao abrir o arquivo para leitura." << std::endl;
            return;
        }
        
        json macrosInfo = fm_in.readJson();
        fm_in.close();

        FileManager fm_out("./packages.json", std::ios::out);
        if (!fm_out.is_open()) {
            std::cerr << "Erro ao abrir o arquivo para escrita." << std::endl;
            return;
        }

        macrosInfo["Macros"].push_back(macro);
        fm_out.writeJson(macrosInfo);
        fm_out.close();
        LOG("macro salva com sucesso");
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
