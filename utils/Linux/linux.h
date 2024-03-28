#ifdef __linux__
#ifndef LINUX_H
#define LINUX_H

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
#endif