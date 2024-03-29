#include <Logging/logging.h>
#include <GenericCommand/genericcommand.h>

int main(int argc, char *argv[]){

    PathManager pm;
    GenericCommand gc;

    if(!pm.exists("./tmp")){
        pm.createDirectory("./tmp", true);
    }

    gc.process("Python", "instalation-commands");
    return 0;
} 
