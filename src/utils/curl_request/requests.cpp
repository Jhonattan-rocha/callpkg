#include "requests.h"
#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

Requests::Requests(){

};

size_t Requests::WriteCallback(void *contents, size_t size, size_t nmemb, std::string *buffer) {
    size_t total_size = size * nmemb;
    buffer->append((char*)contents, total_size);
    return total_size;
};

// Função de callback para processar os cabeçalhos da resposta
size_t Requests::HeaderCallback(char *buffer, size_t size, size_t nitems, std::string *headers) {
    size_t total_size = size * nitems;
    headers->append(buffer, total_size);
    return total_size;
};

std::unordered_map<std::string, std::string> Requests::get(const std::string& url, const std::unordered_map<std::string, std::string> headers_map){
    std::unordered_map<std::string, std::string> response;
    
    std::string response_buffer;
    std::string headers_buffer;

    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    if(curl) {
        // Configura a URL
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // Configura a função de callback para receber os dados
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_buffer);

        // Configura a função de callback para receber os cabeçalhos
        curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, HeaderCallback);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, &headers_buffer);

        // Cabeçalhos personalizados
        struct curl_slist *headers = NULL;
        
        if(headers_map.size() > 0){
            for(const auto& h : headers_map){
                std::string header;
                header.append(h.first);
                header.append(": ");
                header.append(h.second);
                headers = curl_slist_append(headers, header.c_str());
            }
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        }

        // Realiza a solicitação
        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
            std::cerr << "Erro ao realizar a solicitação: " << curl_easy_strerror(res) << std::endl;

        // Obter o código de resposta
        long response_code;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
        response["status_code"] = std::to_string(response_code);

        // Limpa o objeto CURL
        curl_easy_cleanup(curl);

        // Libera a lista de cabeçalhos
        curl_slist_free_all(headers);
    }

    response["response_body"] = response_buffer;
    response["headers"] = headers_buffer;
    return response;
};

std::unordered_map<std::string, std::string> Requests::post(const std::string& url, const std::unordered_map<std::string, std::string> headers, const std::unordered_map<std::string, std::string> data){
    std::unordered_map<std::string, std::string> response;

    return response;
};
std::unordered_map<std::string, std::string> Requests::patch(const std::string& url, const std::unordered_map<std::string, std::string> headers, const std::unordered_map<std::string, std::string> data){
    std::unordered_map<std::string, std::string> response;

    return response;
};
std::unordered_map<std::string, std::string> Requests::put(const std::string& url, const std::unordered_map<std::string, std::string> headers, const std::unordered_map<std::string, std::string> data){
    std::unordered_map<std::string, std::string> response;

    return response;
};
void del(const std::string& url, const std::unordered_map<std::string, std::string> headers, const std::unordered_map<std::string, std::string> data){

};
