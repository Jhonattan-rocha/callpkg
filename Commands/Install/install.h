// install.h

#ifndef INSTALL_H
#define INSTALL_H

#include <PackagesManager/packagesmanager.h>
#include <Validate/validate.h>
#include <Logging/logging.h>
#include <StringTools/stringtools.h>
#include <Exec/exec.h>

class Install
{
public:
    Install();
    ~Install();
    void process(const std::string& name);
};


#endif