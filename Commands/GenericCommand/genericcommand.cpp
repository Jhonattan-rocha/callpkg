// genericcommands.cpp

#include "genericcommand.h"

GenericCommand::GenericCommand(){}

GenericCommand::~GenericCommand(){}

void GenericCommand::process(const std::string& name, const std::string& commandName, std::vector<std::string>& args){
    PackagesManager pm;
    StringTools st;
    Validate val;
    Exec ex;

    if(!val.hasCommand(commandName, name)){
        LOGERR("Comando não encontrado ou não mapeado!");
        return;
    }

    json pack = pm.recover_informations(name);

    std::string current_platform = val.getPlatform();
    current_platform = st.lowercase(current_platform);
    auto platforms = pack["Platforms"];

    this->downloadFilesDependences(pack);

    for (const auto& platform : platforms) {
        if (platform.contains(current_platform)) {
            auto platformInfo = platform[current_platform];
            for(const auto& infos : platformInfo){
                if (infos.contains(commandName)) {
                    auto genericCommands = infos[commandName];
                    for (const auto& command : genericCommands) {
                        LOG("executing command: ");
                        LOG(command);

                        std::string command_str = (std::string) command;
                        int args_count = st.count(command_str, "{}");
                        if(args_count >= 1){
                            std::vector<std::string> result_args = this->processFirstN(args_count, &args);
                            command_str = st.format_string(command_str, result_args);
                        }

                        std::pair<std::string, int> result = ex.exec(command_str);
                        if (result.second == 0) {
                            LOG(result.first);
                        } else {
                            LOGERR(result.first);
                        }
                    }
                } else {
                    LOGERR("Plataforma não possui comandos de instalação");
                }
            }
            break;
        }
    }
}

void GenericCommand::downloadFilesDependences(const json& data){

    if(data["URL-Downloads"].size() < 1){
        return;
    }

    Requests req;
    StringTools st;
    PathManager pm;

    for(const auto& url : data["URL-Downloads"]){
        std::unordered_map<std::string, std::string> response = req.get(url, {});
        int status_code = std::stoi(response["status_code"]);
        if(status_code >= 200 && status_code <= 299){
            std::string file_name = st.split(url, '/').back();
            FileManager fm(pm.join_paths({".", "tmp", file_name}), std::ios::out | std::ios::binary);
            fm.write(response["response_body"]);
            fm.close();
        }
    }
}

std::vector<std::string> GenericCommand::processFirstN(int count, std::vector<std::string>* temp) {
    std::vector<std::string> result;
    if (count <= temp->size()) {
        for (int i = 0; i < count; ++i) {
            result.push_back(temp->at(i));
        }
        temp->erase(temp->begin(), temp->begin() + count);
    } else {
        LOGERR("Quantidade inválida");
        return {};
    }

    return result;
}

void GenericCommand::macro(const std::string& name, std::vector<std::string>& args){
    PackagesManager pm;
    StringTools st;
    Exec ex;

    json macro = pm.get_macro(name);

    for (const auto& command : macro["commands"]) {
        LOG("executing command: ");
        LOG(command);

        std::string command_str = (std::string) command;
        int args_count = st.count(command_str, "{}");
        if(args_count >= 1){
            std::vector<std::string> result_args = this->processFirstN(args_count, &args);
            command_str = st.format_string(command_str, result_args);
        }

        std::string interpreter = macro["interpreter"];
        if(macro.contains("interpreter") && interpreter.length() > 0){
            command_str = interpreter + " " + command_str;
        }

        std::pair<std::string, int> result = ex.exec(command_str);

        if (result.second == 0) {
            LOG(result.first);
        } else {
            LOGERR(result.first);
        }
    }
}

void GenericCommand::create_macro(){
    StringTools st;
    PackagesManager pck;

    json macro;

    LOG("Digite o nome da macro: ");
    std::string name = "";
    
    while (name.length() == 0){
        std::getline(std::cin, name);
        name = st.lowercase(name);
        name = st.strip(name);
        if(name.length() == 0){
            LOGERR("Inválido, digite novamente");
        }
    }
    
    macro["name"] = name;

    LOG("Digite o interpretador da macro(n/a para vazio, o padrão será o cmd/bash): ");
    std::string interpreter = "";
    std::getline(std::cin, interpreter);
    if(st.lowercase(interpreter) == "n/a"){
        interpreter = "";
    }
    macro["interpreter"] = interpreter;
    macro["commands"] = json::array();

    LOG("Agora digite os comandos da macro(digite n/a para parar): ")
    while (true){
        std::string command;
        LOG("comando: ");
        std::getline(std::cin, command);
        if(st.lowercase(command) == "n/a"){
            break;
        }
        macro["commands"].push_back(command);
    }

    pck.save_macro(macro);
}
