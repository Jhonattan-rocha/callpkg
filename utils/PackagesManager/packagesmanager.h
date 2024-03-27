//packagesmanager.h

#include <FileManager/filemanager.h>
#include <PathManager/pathmanager.h>
#include <StringTools/stringtools.h>

class PackagesManager
{
public:
    PackagesManager();
public:
    json recover_informations(const std::string& name);
    void save_informations(const json& info);
    json getTemplate();
};
