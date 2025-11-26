#ifndef EchoCommand_h
#define EchoCommand_h

#include "MultilineReader.h"
#include "Command.h"
#include "FileOperations.h"

class EchoCommand: public Command {
public:
	std::string execute(std::vector<std::string> commandVec) override;
};
#endif
