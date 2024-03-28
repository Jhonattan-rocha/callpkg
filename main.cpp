#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <Install/install.h>

int main(int argc, char *argv[]){
    Install ins;
    ins.process("Chocolatey");
    system("pause");
    return 0;
}
