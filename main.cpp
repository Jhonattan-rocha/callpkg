#include <Logging/logging.h>
#include <curl_request/requests.h>
#include <FileManager/filemanager.h>

int main(int argc, char *argv[]){
    Requests req;
    
    std::unordered_map<std::string, std::string> response = req.get("https://www.python.org/ftp/python/3.12.2/python-3.12.2-amd64.exe", {});

    FileManager fm("../python-3.12.2-amd64.exe", std::ios::out | std::ios::binary);

    fm.write(response["response_body"]);

    LOG(response["headers"]);
    
    fm.close();
    system("pause");
    return 0;
} 
