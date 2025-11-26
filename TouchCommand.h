#ifndef TouchCommand_h
#define TouchCommand_h

#include "Command.h"
#include "FileOperations.h"
#include "ArgumentChecker.h"

class TouchCommand: public Command {
public:
	std::string execute(std::vector<std::string> commandVec) override;
};
#endif

