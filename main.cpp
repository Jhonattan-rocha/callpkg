#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <curl_request/requests.h>
#include <FileManager/filemanager.h>
#include <Node/nodeManager.h>

int main(int argc, char *argv[]){
    Requests req;
    
    std::unordered_map<std::string, std::string> response = req.get("https://www.youtube.com/watch?v=StPJhWmfzjU&list=RDStPJhWmfzjU&start_radio=1", {});
    FileManager fm("../yout.html", std::ios_base::out);

    fm.write(response["response_body"]);
    
    fm.close();

    std::cout << response["headers"] << std::endl;

    system("pause");
    return 0;
}
