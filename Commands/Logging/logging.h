#ifndef LOGGING_H
#define LOGGING_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define LOG(message) std::cout << message << std::endl;
#define LOGERR(message) std::cerr << message << std::endl;

#endif // LOGGING_H
