#ifndef HeadCommand_h
#define HeadCommand_h

#include "MultilineReader.h"
#include "Command.h"
#include <sstream>

class HeadCommand : public Command {

public:
	std::string execute(std::vector<std::string> commandVec) override;
};
#endif

