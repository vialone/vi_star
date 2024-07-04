#pragma once

#include <iostream>
#include <string>

#ifdef DEBUG_MODE
#define DEBUG(x) std::cout << "[DEBUG] " << x << "\n";
#else
#define DEBUG(x)
#endif

#define THROW(msg) DEBUG(std::string(msg)); exit(-1);
