#ifndef CommandChecker_h
#define CommandChecker_h

#include "CommandMenager.h"
#include "ArgumentChecker.h"

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>


class CommandChecker
{
public:
	static bool checkCommands(std::vector<std::vector<std::string>>& commands);

};

#endif
