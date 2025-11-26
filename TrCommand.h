#ifndef TrCommand_h
#define TrCommand_h

#include "Command.h"
#include "MultilineReader.h"


class TrCommand: public Command {
public:
	std::string execute(std::vector<std::string> commandVec) override;

};
#endif
