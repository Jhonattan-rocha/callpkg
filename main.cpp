#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <curl_request/requests.h>
#include <FileManager/filemanager.h>
#include <Node/nodeManager.h>

int main(int argc, char *argv[]){

    FileManager fm("../page.html", std::ios_base::out);

    Requests req;
    
    std::unordered_map<std::string, std::string> response = req.get("https://www.google.com/search?q=403+http+response+code&rlz=1C1CHZN_pt-BRBR1052BR1052&oq=403+http+res&gs_lcrp=EgZjaHJvbWUqCQgCEAAYExiABDIGCAAQRRg5MgkIARAAGBMYgAQyCQgCEAAYExiABDIMCAMQABgPGBMYFhgeMgoIBBAAGBMYFhgeMgoIBRAAGBMYFhgeMgoIBhAAGBMYFhgeMgoIBxAAGBMYFhgeMgoICBAAGBMYFhgeMgoICRAAGBMYFhge0gEINDAwMWowajeoAgiwAgE&sourceid=chrome&ie=UTF-8", {});

    fm.write(response["response_body"]);

    return 0;
}
