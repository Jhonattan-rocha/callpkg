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

    // comandos
    commands["get-instalation"] = [](const std::vector<std::string>& argsc){
        Validate val;
        val.isSoftwareInstalled(argsc[0]);
    };

    commands["download"] = [](const std::vector<std::string>& argsc){
        Requests req;
        StringTools st;
        PathManager pm;
        std::unordered_map<std::string, std::string> response = req.get(argsc[0], {});
        int status = std::stoi(response["status_code"]);
        if(status >= 200 && status <= 299){
            std::string file_name = st.split(argsc[0], '/').back();
            FileManager fm((argsc.size() == 2)? argsc[1]:pm.join_paths({".", "tmp", file_name}), std::ios::out | std::ios::binary);
            fm.write(response["response_body"]);
            fm.close();
        }
    };

    commands["macro"] = [](const std::vector<std::string>& argsc){
        GenericCommand gm;
        std::vector<std::string> args(argsc.begin(), argsc.end());
        std::string macro = args[0];
        args.erase(args.begin());
        gm.macro(macro, args);
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
