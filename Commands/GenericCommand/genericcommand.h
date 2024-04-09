// genericcommands.h

#ifndef GENERICCOMMANDS_H
#define GENERICCOMMANDS_H

#include <PackagesManager/packagesmanager.h>
#include <Validate/validate.h>
#include <Logging/logging.h>
#include <StringTools/stringtools.h>
#include <curl_request/requests.h>
#include <Exec/exec.h>

class GenericCommand
{
public:
    GenericCommand();
    ~GenericCommand();
    void process(const std::string& name, const std::string& commandName, std::vector<std::string>& args);
    std::vector<std::string> processFirstN(int count, std::vector<std::string>* temp);
    void macro(const std::string& name, std::vector<std::string>& args);
private:
    void downloadFilesDependences(const json& urls);
};

#endif