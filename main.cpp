#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "src/utils/curl_request/requests.h"

int main(int argc, char *argv[]){
    std::cout << "Hellow World" << std::endl;

    Requests req;
    std::unordered_map response = req.get("https://stackoverflow.com/questions/347949/how-to-convert-a-stdstring-to-const-char-or-char", {});
    
    for(const auto& res : response){
        std::cout << res.first << res.second << std::endl;
    }
    
    return 0;
}
