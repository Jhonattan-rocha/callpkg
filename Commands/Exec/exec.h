// exec.h

#include <memory>
#include <stdexcept>
#include <string>
#include <sstream>

class Exec
{
public:
    Exec();
    ~Exec();
    std::string exec(const std::string& cmd);
};

