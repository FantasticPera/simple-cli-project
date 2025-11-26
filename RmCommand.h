#ifndef RmCommand_h
#define RmCommand_h

#include "Command.h"
#include "FileOperations.h"
#include "ArgumentChecker.h"

class RmCommand: public Command {
public:
	std::string execute(std::vector<std::string> commandVec) override;

};
#endif
