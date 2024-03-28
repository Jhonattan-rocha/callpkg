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
