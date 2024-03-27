// packagesmanager.cpp

#include "packagesmanager.h"

PackagesManager::PackagesManager(){}

json PackagesManager::recover_informations(const std::string& name){
    FileManager fm("./packages.json", std::ios_base::in);
    json return_software_info;
    json softwaresInfo = fm.readJson();

    for (auto& software : softwaresInfo["Softwares"]) {
        std::string softwareName = software["software-name"];
        if(softwareName == name){
            return_software_info = software;
            break;
        }
    }

    return return_software_info;
}

void PackagesManager::save_informations(const json& info){
    try {
        FileManager fm_in("./packages.json", std::ios_base::in);
        if (!fm_in.is_open()) {
            std::cerr << "Erro ao abrir o arquivo para leitura." << std::endl;
            return;
        }
        
        json softwaresInfo = fm_in.readJson();
        fm_in.close();

        FileManager fm_out("./packages.json", std::ios_base::out);
        if (!fm_out.is_open()) {
            std::cerr << "Erro ao abrir o arquivo para escrita." << std::endl;
            return;
        }

        softwaresInfo.push_back(info);
        fm_out.writeJson(softwaresInfo);
        fm_out.close();
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

json PackagesManager::getTemplate(){
    FileManager fm_in("./packages-template.json", std::ios_base::in);
    if (!fm_in.is_open()) {
        std::cerr << "Erro ao abrir o arquivo para leitura." << std::endl;
        return;
    }
    json data = fm_in.readJson();
    if(data["Softwares"].size() != 1){
        std::cerr << "Erro com o arquivo template." << std::endl;
        return;
    }
    json template = data["Softwares"][0];

    return template;
}

