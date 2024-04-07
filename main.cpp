#include <Logging/logging.h>
#include <GenericCommand/genericcommand.h>
#include <PathManager/pathmanager.h>
#include <Validate/validate.h>
#include <locale>
#include <unordered_map>

int main(int argc, char *argv[]){
    setlocale(LC_ALL, "Portuguese");
    GenericCommand gm;
    PathManager pm;
    PackagesManager pk;
    Validate val;

    std::unordered_map<std::string, std::function<void(const std::vector<std::string>& argsc)>> commands;
    commands["get-instalation"] = [](const std::vector<std::string>& argsc){
        Validate val;
        val.isSoftwareInstalled(argsc[0]);
    };

    if(!pm.exists(pm.join_paths({".", "tmp"}))){
        pm.createDirectory(pm.join_paths({".", "tmp"}), true);
    }

    std::vector<std::string> args(argv, argv + argc);
    args.erase(args.begin()); // tirando o nome do arquivo dos args

    if(args.size() == 0){
        LOGERR("Vazio é inválido!");
        return 1;
    }
    
    std::string name = args[1];
    std::string command = args[0];
    args.erase(args.begin()); // tirando o comando dos args

    try{
        auto func = commands.at(command);
        func(args);
    }catch(std::exception& ex){
        if(!val.hasCommand(command, name)){
            LOGERR("Comando não encontrado ou não mapeado!");
            return 1;
        }

        args.erase(args.begin()); // tirando o target dos args
        gm.process(name, command, args);
    }
    return 0;
}
