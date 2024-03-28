#ifdef __linux__

#include <fstream>
#include <iostream>
#include <string>

class Linux
{
public:
    Linux();
    ~Linux();
    std::string getLinuxDistribution();
};


#endif