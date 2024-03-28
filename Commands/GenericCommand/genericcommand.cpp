// genericcommands.cpp

#include "genericcommand.h"

GenericCommand::GenericCommand(){}

GenericCommand::~GenericCommand(){}

void GenericCommand::process(const std::string& name, const std::string& commandName){
    PackagesManager pm;
    StringTools st;
    Validate val;
    Exec ex;

    json pack = pm.recover_informations(name);
    std::string current_platform = val.getPlatform();
    current_platform = st.lowercase(current_platform);
    auto platforms = pack["Platforms"];

    for (const auto& platform : platforms) {
        if (platform.contains(current_platform)) {
            auto platformInfo = platform[current_platform];
            for(const auto& infos : platformInfo){
                if (infos.contains(commandName)) {
                    auto genericCommands = infos[commandName];
                    for (const auto& command : genericCommands) {
                        std::pair<std::string, int> result = ex.exec(command);
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
