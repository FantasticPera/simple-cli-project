#ifndef WcCommand_h
#define WcCommand_h

#include "Command.h"
#include <sstream>
#include "MultilineReader.h"



class WcCommand: public Command {
public:
	std::string execute(std::vector<std::string> commandVec) override;
	static std::string countWC(std::string arg, std::string option);

};

#endif
