//requets.h
#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <unordered_map>
#include <curl/curl.h>
#include <unordered_map>
#include <Logging/logging.h>

class Requests{    
public:
    Requests();
    std::unordered_map<std::string, std::string> get(const std::string& url, const std::unordered_map<std::string, std::string>& headers_map);
    std::unordered_map<std::string, std::string> post(const std::string& url, const std::unordered_map<std::string, std::string>& headers_map, const std::unordered_map<std::string, std::string> data_map);
    std::unordered_map<std::string, std::string> patch(const std::string& url, const std::unordered_map<std::string, std::string>& headers_map, const std::unordered_map<std::string, std::string> data_map);
    std::unordered_map<std::string, std::string> put(const std::string& url, const std::unordered_map<std::string, std::string>& headers_map, const std::unordered_map<std::string, std::string> data_map);
    std::unordered_map<std::string, std::string> del(const std::string& url, const std::unordered_map<std::string, std::string>& headers_map, const std::unordered_map<std::string, std::string> data_map);
private:
    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *buffer);
    static size_t HeaderCallback(void *buffer, size_t size, size_t nitems, void *headers);
};


#endif