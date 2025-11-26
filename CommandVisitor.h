#ifndef CommandVisitor_h
#define CommandVisitor_h

#include "Command.h"
#include "EchoCommand.h"
#include "TouchCommand.h"
#include "WcCommand.h"
#include "TimeCommand.h"
#include "DateCommand.h"
#include "PromptCommand.h"
#include "TruncateCommand.h"
#include "RmCommand.h"
#include "TrCommand.h"
#include "HeadCommand.h"
#include "BatchCommand.h"
//If you need to add more commands

#include <string>
#include <memory>

class CommandVisitor
{
public:
	static std::unique_ptr<Command> visitCommand(std::string commandName);
};

#endif