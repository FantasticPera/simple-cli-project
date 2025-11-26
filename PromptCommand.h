#ifndef PromptCommand_h
#define PromptCommand_h

#include <iostream>
#include "Command.h"
#include "CommandMenager.h"

class PromptCommand: public Command {

public:
	std::string execute(std::vector<std::string> commandVec) override;

};
#endif

