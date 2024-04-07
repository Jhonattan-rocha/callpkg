// Validadte.cpp

#include "validate.h"

Validate::Validate(){}

Validate::~Validate(){}

bool Validate::isAdmin(){
    #ifdef _WIN32
        BOOL b;
        SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
        PSID AdministratorsGroup;

        b = AllocateAndInitializeSid(
            &NtAuthority,
            2,
            SECURITY_BUILTIN_DOMAIN_RID,
            DOMAIN_ALIAS_RID_ADMINS,
            0, 0, 0, 0, 0, 0,
            &AdministratorsGroup);

        if (b == TRUE)
        {
            if (CheckTokenMembership(NULL, AdministratorsGroup, &b) == FALSE)
            {
                b = FALSE;
            }
            FreeSid(AdministratorsGroup);
        }
        return (b == TRUE);
    #endif
}

bool Validate::execPolicyValidateForPowerShell(const std::string& policy_name="AllSigned"){
    if(this->isAdmin()){
        StringTools st;
        Exec ex;
        std::pair<std::string, int> policy = ex.exec("powershell; Get-ExecutionPolicy");
        if(policy.second == 0 && st.lowercase(policy.first) == "restricted"){
            std::pair<std::string, int> result = ex.exec("powershell; Set-ExecutionPolicy -ExecutionPolicy "+policy_name+" -Scope CurrentUser");
            if(result.second == 0){
                LOG(result.first);
                return true;
            }else{
                LOGERR(result.first);
                return false;
            }
        }else{
            LOGERR(policy.first);
            return false;
        }
    }else{
        LOGERR("Politica de execução do powershell não permite instalação de softwares de terceiros, é necessário privilégios de administrador para poder corrigir");
        return false;
    }
}

std::string Validate::getPlatform(){
    #ifdef _WIN32
        return "windows";
    #elif __linux__
        return "linux";
    #elif __APPLE__
        return "mac";
    #else
        return "unnkow";
    #endif
}

bool Validate::isSoftwareInstalled(const std::string& softwareName) {
    std::string command;
    #ifdef _WIN32
        command = "where " + softwareName; // Comando 'where' no Windows procura pelo executável do software
    #elif __linux__
        command = "which " + softwareName; // Comando 'which' no Linux procura pelo executável do software
    #else
        #error "Plataforma não suportada"
    #endif
        Exec ex;
        std::pair<std::string, int> result = ex.exec(command);
        if(result.second == 0){
            LOG(result.first);
        }else{
            LOGERR(result.first);
        }
        return result.second == 0;
}

bool Validate::hasCommand(const std::string& commandName, const std::string& name){
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
                    return true;
                } else {
                    return false;
                }
            }
            break;
        }
    }
    
    return false;
}
