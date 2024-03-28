// exec.h

#ifndef EXEC_H
#define EXEC_H

#include <memory>
#include <stdexcept>
#include <string>
#include <sstream>
#include <unistd.h>

class Exec
{
public:
    Exec();
    ~Exec();
    std::pair<std::string, int> exec(const std::string& cmd);
};

#endif

