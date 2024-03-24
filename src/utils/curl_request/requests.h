//requets.h
#ifndef REQUESTS_H
#define REQUESTS_H

#include <string>
#include <unordered_map>

class Requests{    
public:
    Requests();
    std::unordered_map<std::string, std::string> get(const std::string& url, const std::unordered_map<std::string, std::string> headers);
    std::unordered_map<std::string, std::string> post(const std::string& url, const std::unordered_map<std::string, std::string> headers, const std::unordered_map<std::string, std::string> data);
    std::unordered_map<std::string, std::string> patch(const std::string& url, const std::unordered_map<std::string, std::string> headers, const std::unordered_map<std::string, std::string> data);
    std::unordered_map<std::string, std::string> put(const std::string& url, const std::unordered_map<std::string, std::string> headers, const std::unordered_map<std::string, std::string> data);
    void del(const std::string& url, const std::unordered_map<std::string, std::string> headers, const std::unordered_map<std::string, std::string> data);
private:
    size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *buffer);
    size_t HeaderCallback(char *buffer, size_t size, size_t nitems, std::string *headers);
};

#endif