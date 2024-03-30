// genericcommands.cpp

#include "genericcommand.h"

GenericCommand::GenericCommand(){}

GenericCommand::~GenericCommand(){}

void GenericCommand::process(const std::string& name, const std::string& commandName, std::vector<std::string>& args){
    PackagesManager pm;
    StringTools st;
    Validate val;
    Exec ex;

    json pack = pm.recover_informations(name);

    if(!pack.is_object()){
        return;
    }

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
                            command_str = st.format_string_std(command_str, result_args[0]);
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
            return;
        }
    }

    LOGERR("Nenhuma requisição para download teve sucesso");
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
