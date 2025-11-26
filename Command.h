#ifndef Command_h
#define Command_h

#include <string>
#include <vector>
#include <algorithm>
#include "ArgumentChecker.h"
#include "FileOperations.h"

class Command {
public:
    virtual ~Command() = default;
    virtual std::string execute(std::vector<std::string> commandVec) = 0;
    static std::string readArgumentOrFile(std::string arg);
    static int findInRedIndex(std::vector<std::string> commandVec);
    static int findOutRedIndex(std::vector<std::string> commandVec);
};

#endif
