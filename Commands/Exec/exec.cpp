//exec.cpp

#include "exec.h"

Exec::Exec(){}

Exec::~Exec(){}

std::string Exec::exec(const std::string& cmd) {
    std::stringstream result;
    char buffer[128];
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    try {
        while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
            result << buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw; // Re-throw the exception
    }
    pclose(pipe);
    return result.str();
}