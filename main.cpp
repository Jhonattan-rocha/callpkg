#include <Logging/logging.h>
#include <GenericCommand/genericcommand.h>
#include <PathManager/pathmanager.h>

int main(int argc, char *argv[]){
    GenericCommand gm;
    PathManager pm;

    if(!pm.exists(pm.join_paths({".", "tmp"}))){
        pm.createDirectory(pm.join_paths({".", "tmp"}), true);
    }

    std::vector<std::string> temp(argv, argv + argc);
    temp.erase(temp.begin());
    
    gm.process("Python", "instalation-commands", temp);    
    return 0;
} 
