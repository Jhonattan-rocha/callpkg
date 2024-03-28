#include "requests.h"

Requests::Requests(){}

size_t Requests::WriteCallback(void *contents, size_t size, size_t nmemb, void *buffer) {
    size_t total_size = size * nmemb;
    ((std::string*)buffer)->append(static_cast<char*>(contents), total_size);
    return total_size;
}

size_t Requests::HeaderCallback(void *buffer, size_t size, size_t nitems, void *headers) {
    size_t total_size = size * nitems;
    ((std::string*)headers)->append(static_cast<char*>(buffer), total_size);
    return total_size;
}

std::unordered_map<std::string, std::string> Requests::get(const std::string& url, const std::unordered_map<std::string, std::string>& headers_map) {
    std::unordered_map<std::string, std::string> response;
    std::string response_buffer;
    std::string headers_buffer;

    LOG("executing: get request for " + url);
    try{
        CURL *curl;
        CURLcode res;
        curl = curl_easy_init();
        if(curl) {
            // Configura a URL
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
            // Configura a função de callback para receber os dados
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Requests::WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_buffer);

            // Configura a função de callback para receber os cabeçalhos
            curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, Requests::HeaderCallback);
            curl_easy_setopt(curl, CURLOPT_HEADERDATA, &headers_buffer);

            // Cabeçalhos personalizados
            struct curl_slist *headers = NULL;
            if(headers_map.size() > 0){
                for (const auto& h : headers_map) {
                    std::string header = h.first + ": " + h.second;
                    headers = curl_slist_append(headers, header.c_str());
                }
                curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
            }

            // Realiza a solicitação
            res = curl_easy_perform(curl);
            if(res != CURLE_OK)
                LOGERR("Request error: " + std::string(curl_easy_strerror(res)));

            // Obter o código de resposta
            long response_code;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
            response["status_code"] = std::to_string(response_code);
            LOG("Status code: " + std::to_string(response_code));

            // Limpa o objeto CURL
            curl_easy_cleanup(curl);

            // Libera a lista de cabeçalhos
            curl_slist_free_all(headers);
        }

        response["response_body"] = response_buffer;
        response["headers"] = headers_buffer;
    }catch(std::exception& e){
        LOGERR("Error in request: ");
        LOGERR(e.what());
    }

    return response;
}


std::unordered_map<std::string, std::string> Requests::post(const std::string& url, const std::unordered_map<std::string, std::string>& headers_map, const std::unordered_map<std::string, std::string> data_map) {
    std::unordered_map<std::string, std::string> response;
    std::string response_buffer;
    std::string headers_buffer;

    LOG("executing: post request for " + url);
    try {
        CURL *curl;
        CURLcode res;
        curl = curl_easy_init();
        if (curl) {
            // Configura a URL
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

            // Configura a função de callback para receber os dados
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, this->WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_buffer);

            // Configura a função de callback para receber os cabeçalhos
            curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, this->HeaderCallback);
            curl_easy_setopt(curl, CURLOPT_HEADERDATA, &headers_buffer);
            curl_easy_setopt(curl, CURLOPT_POST, 1L);

            // Cabeçalhos personalizados
            struct curl_slist *headers = NULL;
            for (const auto& h : headers_map) {
                std::string header = h.first + ": " + h.second;
                headers = curl_slist_append(headers, header.c_str());
            }
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

            // Dados POST
            struct curl_slist *data = NULL;
            for (const auto& d : data_map) {
                std::string data_line = d.first + "=" + d.second;
                data = curl_slist_append(data, data_line.c_str());
            }
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);

            // Realiza a solicitação
            res = curl_easy_perform(curl);
            if (res != CURLE_OK)
                LOGERR("Request error: " + std::string(curl_easy_strerror(res)));

            // Obter o código de resposta
            long response_code;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
            response["status_code"] = std::to_string(response_code);
            LOG("Status code: " + std::to_string(response_code));

            // Limpa o objeto CURL
            curl_easy_cleanup(curl);

            // Libera a lista de cabeçalhos
            curl_slist_free_all(headers);

            // Libera a lista de dados
            curl_slist_free_all(data);
        }

        response["response_body"] = response_buffer;
        response["headers"] = headers_buffer;
    }
    catch (std::exception& e) {
        LOGERR("Error in request: ");
        LOGERR(e.what());
    }

    return response; // Adicione essa linha para retornar a resposta
}

std::unordered_map<std::string, std::string> Requests::patch(const std::string& url, const std::unordered_map<std::string, std::string>& headers_map, const std::unordered_map<std::string, std::string> data_map){
    std::unordered_map<std::string, std::string> response;
    std::string response_buffer;
    std::string headers_buffer;

    LOG("executing: patch request for " + url);
    try {
        CURL *curl;
        CURLcode res;
        curl = curl_easy_init();
        if (curl) {
            // Configura a URL
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

            // Configura a função de callback para receber os dados
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, this->WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_buffer);

            // Configura a função de callback para receber os cabeçalhos
            curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, this->HeaderCallback);
            curl_easy_setopt(curl, CURLOPT_HEADERDATA, &headers_buffer);
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PATCH");
            
            // Cabeçalhos personalizados
            struct curl_slist *headers = NULL;
            for (const auto& h : headers_map) {
                std::string header = h.first + ": " + h.second;
                headers = curl_slist_append(headers, header.c_str());
            }
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

            // Dados POST
            struct curl_slist *data = NULL;
            for (const auto& d : data_map) {
                std::string data_line = d.first + "=" + d.second;
                data = curl_slist_append(data, data_line.c_str());
            }
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);

            // Realiza a solicitação
            res = curl_easy_perform(curl);
            if (res != CURLE_OK)
                LOGERR("Request error: " + std::string(curl_easy_strerror(res)));

            // Obter o código de resposta
            long response_code;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
            response["status_code"] = std::to_string(response_code);
            LOG("Status code: " + std::to_string(response_code));

            // Limpa o objeto CURL
            curl_easy_cleanup(curl);

            // Libera a lista de cabeçalhos
            curl_slist_free_all(headers);

            // Libera a lista de dados
            curl_slist_free_all(data);
        }

        response["response_body"] = response_buffer;
        response["headers"] = headers_buffer;
    }
    catch (std::exception& e) {
        LOGERR("Error in request: ");
        LOGERR(e.what());
    }

    return response; // Adicione essa linha para retornar a resposta
}
std::unordered_map<std::string, std::string> Requests::put(const std::string& url, const std::unordered_map<std::string, std::string>& headers_map, const std::unordered_map<std::string, std::string> data_map){
    std::unordered_map<std::string, std::string> response;
    std::string response_buffer;
    std::string headers_buffer;

    LOG("executing: put request for " + url);
    try {
        CURL *curl;
        CURLcode res;
        curl = curl_easy_init();
        if (curl) {
            // Configura a URL
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

            // Configura a função de callback para receber os dados
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, this->WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_buffer);

            // Configura a função de callback para receber os cabeçalhos
            curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, this->HeaderCallback);
            curl_easy_setopt(curl, CURLOPT_HEADERDATA, &headers_buffer);
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");

            // Cabeçalhos personalizados
            struct curl_slist *headers = NULL;
            for (const auto& h : headers_map) {
                std::string header = h.first + ": " + h.second;
                headers = curl_slist_append(headers, header.c_str());
            }
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

            // Dados POST
            struct curl_slist *data = NULL;
            for (const auto& d : data_map) {
                std::string data_line = d.first + "=" + d.second;
                data = curl_slist_append(data, data_line.c_str());
            }
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);

            // Realiza a solicitação
            res = curl_easy_perform(curl);
            if (res != CURLE_OK)
                LOGERR("Request error: " + std::string(curl_easy_strerror(res)));

            // Obter o código de resposta
            long response_code;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
            response["status_code"] = std::to_string(response_code);
            LOG("Status code: " + std::to_string(response_code));

            // Limpa o objeto CURL
            curl_easy_cleanup(curl);

            // Libera a lista de cabeçalhos
            curl_slist_free_all(headers);

            // Libera a lista de dados
            curl_slist_free_all(data);
        }

        response["response_body"] = response_buffer;
        response["headers"] = headers_buffer;
    }
    catch (std::exception& e) {
        LOGERR("Error in request: ");
        LOGERR(e.what());
    }

    return response; // Adicione essa linha para retornar a resposta
}
std::unordered_map<std::string, std::string> Requests::del(const std::string& url, const std::unordered_map<std::string, std::string>& headers_map, const std::unordered_map<std::string, std::string> data_map){
    std::unordered_map<std::string, std::string> response;
    std::string response_buffer;
    std::string headers_buffer;

    LOG("executing: delete request for " + url);
    try {
        CURL *curl;
        CURLcode res;
        curl = curl_easy_init();
        if (curl) {
            // Configura a URL
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

            // Configura a função de callback para receber os dados
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, this->WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_buffer);

            // Configura a função de callback para receber os cabeçalhos
            curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, this->HeaderCallback);
            curl_easy_setopt(curl, CURLOPT_HEADERDATA, &headers_buffer);
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");

            // Cabeçalhos personalizados
            struct curl_slist *headers = NULL;
            for (const auto& h : headers_map) {
                std::string header = h.first + ": " + h.second;
                headers = curl_slist_append(headers, header.c_str());
            }
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

            // Dados POST
            struct curl_slist *data = NULL;
            for (const auto& d : data_map) {
                std::string data_line = d.first + "=" + d.second;
                data = curl_slist_append(data, data_line.c_str());
            }
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);

            // Realiza a solicitação
            res = curl_easy_perform(curl);
            if (res != CURLE_OK)
                LOGERR("Request error: " + std::string(curl_easy_strerror(res)));

            // Obter o código de resposta
            long response_code;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
            response["status_code"] = std::to_string(response_code);
            LOG("Status code: " + std::to_string(response_code));

            // Limpa o objeto CURL
            curl_easy_cleanup(curl);

            // Libera a lista de cabeçalhos
            curl_slist_free_all(headers);

            // Libera a lista de dados
            curl_slist_free_all(data);
        }

        response["response_body"] = response_buffer;
        response["headers"] = headers_buffer;
    }
    catch (std::exception& e) {
        LOGERR("Error in request: ");
        LOGERR(e.what());
    }

    return response; // Adicione essa linha para retornar a resposta
}
