#ifndef BatchCommand_h
#define BatchCommand_h

#include "MultilineReader.h"
#include "Command.h"
#include "FileOperations.h"
#include "Parser.h"
#include "CommandChecker.h"
#include "CommandMenager.h"
#include "CommandVisitor.h"
#include <iostream>
#include <sstream>

class BatchCommand : public Command {
public:
	std::string execute(std::vector<std::string> commandVec) override;
};

#endif
