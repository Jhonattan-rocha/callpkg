// validate.h

#ifndef VALIDATE_H
#define VALIDATE_H

#ifdef _WIN32
#include <windows.h>
#endif

#include <Exec/exec.h>
#include <StringTools/stringtools.h>
#include <Logging/logging.h>
#include <PackagesManager/packagesmanager.h>

class Validate
{
public:
    Validate();
    ~Validate();
    bool isAdmin();
    bool execPolicyValidateForPowerShell(const std::string& policy_name);
    std::string getPlatform();
    bool isSoftwareInstalled(const std::string& softwareName);
    bool hasCommand(const std::string& commandName, const std::string& name);
};

#endif
