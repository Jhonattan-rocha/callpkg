#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <Exec/exec.h>

int main(int argc, char *argv[]){
    Exec ex;
    std::string result = ex.exec("dir");
    std::cout << result << std::endl;
    system("pause");
    return 0;
}
