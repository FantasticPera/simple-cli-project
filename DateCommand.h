#ifndef DateCommand_h
#define DateCommand_h


#include "Command.h"
#include <sstream>
#include <ctime>
#include <iomanip>
#include "FileOperations.h"

class DateCommand: public Command {
public:
	std::string execute(std::vector<std::string> commandVec) override;

};

#endif