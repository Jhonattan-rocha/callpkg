#ifdef __linux__

#include <fstream>
#include <iostream>
#include <string>

class Linux
{
private:
    std::string exec(const char* cmd);
public:
    Linux();
    ~Linux();
    std::string getLinuxDistribution();
};


#endif