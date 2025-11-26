#ifndef TruncateCommand_h
#define TruncateCommand_h

#include "Command.h"
#include "FileOperations.h"
#include "ArgumentChecker.h"

class TruncateCommand: public Command {
public:
	std::string execute(std::vector<std::string> commandVec) override;



};
#endif
