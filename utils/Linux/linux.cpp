#ifdef __linux__

//linux.h
#include "linux.h"

Linux::Linux(/* args */)
{
}

Linux::~Linux()
{
}

std::string Linux::exec(const char* cmd) {
    std::string result, line;
    FILE* pipe = popen(cmd, "r");
    if (!pipe) {
        return "";
    }
    while (fgets(line.c_str(), sizeof(line), pipe) != NULL) {
        result += line;
    }
    pclose(pipe);
    return result;
}

// Função para determinar a distribuição Linux atual
std::string Linux::getLinuxDistribution() {
    std::string distro;
    // Tentativa de identificar a distribuição usando /etc/os-release
    std::ifstream os_release("/etc/os-release");
    if (os_release.is_open()) {
        std::string line;
        while (getline(os_release, line)) {
            if (line.find("ID=") == 0) {
                distro = line.substr(line.find("=") + 1);
                break;
            }
        }
    }
    os_release.close();
    if (!distro.empty()) {
        return distro;
    }
    // Tentativa de identificar a distribuição usando lsb_release
    std::string lsb_release_result = exec("lsb_release -si");
    if (!lsb_release_result.empty()) {
        return lsb_release_result;
    }
    // Se nenhum método funcionar, retornar uma string vazia ou um valor padrão
    return "";
}


#endif