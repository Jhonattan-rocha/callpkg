#include "stringtools.h"

StringTools::StringTools() {}

std::vector<std::string> StringTools::split(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    size_t start = 0;

    while (start < str.length()) {
        // Ignora espaços em branco no início
        while (start < str.length() && isspace(str[start]))
            ++start;

        if (str[start] == '"') {
            // Se encontrou uma aspa, encontra a próxima aspa
            size_t end = str.find('"', start + 1);
            if (end == std::string::npos) {
                // Aspa de fechamento não encontrada
                result.push_back(str.substr(start));
                break;
            }

            // Adiciona a substring entre as aspas
            result.push_back(str.substr(start + 1, end - start - 1));
            start = end + 1;
        } else {
            // Encontra a próxima ocorrência do delimitador
            size_t end = str.find(delimiter, start);
            // Adiciona a substring entre o início e o delimitador (ou o final se não encontrar)
            result.push_back(str.substr(start, end - start));
            // Atualiza o índice de início para além do delimitador (ou o final)
            start = (end == std::string::npos) ? end : end + 1;
        }
    }

    return result;
}

std::string StringTools::limit_str(int limit, std::string value){
    std::string result;
    result = value.substr(size_t(0), size_t(limit));
    return this->strip(result);
}

std::string StringTools::join(std::vector<std::string> parts, char delimiter) {
    std::string result;

    for (const auto& part : parts){
        result = result + part + delimiter;
    }

    return result;
}

std::string StringTools::lstrip(const std::string& s) {
    size_t start = s.find_first_not_of(" \t\n\r\f\v");
    return (start == std::string::npos) ? "" : s.substr(start);
}

std::string StringTools::rstrip(const std::string& s) {
    size_t end = s.find_last_not_of(" \t\n\r\f\v");
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string StringTools::strip(const std::string& s) {
    return rstrip(lstrip(s));
}

std::vector<size_t> StringTools::find(const std::string& search, const std::string& str, const bool all){
    std::vector<size_t> result;

    size_t pos = str.find(search);
    result.push_back(pos);

    if(all){
        while (pos != std::string::npos) {
            pos = str.find(search, pos + 1);
            result.push_back(pos);
        }
    }

    return result;
}

std::string StringTools::uppercase(const std::string& str){
    std::string result;

    for(char c : str){
        result += std::toupper(c);
    }

    return result;
}

std::string StringTools::lowercase(const std::string& str){
    std::string result;

    for(char c : str){
        result += std::tolower(c);
    }

    return result;
}

int StringTools::count(const std::string& str, const std::string& sub) {
    int count = 0;
    size_t pos = 0;
    
    while ((pos = str.find(sub, pos)) != std::string::npos) {
        ++count;
        pos += sub.length();
    }
    
    return count;
}

std::string StringTools::replace(const std::string& str, const std::regex& reg, const std::string& repl){
    std::string response;

    response = std::regex_replace(str, reg, repl);

    return response;
}
