// install.cpp

#include "install.h"

Install::Install(){}

Install::~Install(){}

void Install::process(const std::string& name){
    PackagesManager pm;
    StringTools st;
    Validate val;
    Exec ex;

    json pack = pm.recover_informations(name);
    std::string current_platform = val.getPlatform();
    current_platform = st.lowercase(current_platform);

    if(pack){
        auto platforms = pack["Platforms"];
        auto commands = platforms[current_platform];

        for(const auto& command : commands){
            std::pair<std::string, int> result = ex.exec(command);
            if(result.second == 0){
                LOG(result.first);
            }else{
                LOGERR(result.first);
            }
        }
    }else{
        LOGERR("Software não foi encontrado nas informações registradas")
    }
}
