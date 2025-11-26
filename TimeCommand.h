#ifndef TimeCommand_h
#define TimeCommand_h

#include "Command.h"
#include <sstream>
#include <ctime>
#include <iomanip>
#include "FileOperations.h"


class TimeCommand: public Command {
public:
	std::string execute(std::vector<std::string> commandVec) override;

};

#endif