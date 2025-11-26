#include "CommandVisitor.h"

using namespace std;


unique_ptr<Command> CommandVisitor::visitCommand(string commandName) {
	if (commandName == "echo") {
		return make_unique<EchoCommand>();
	}
	if (commandName == "touch") {
		return make_unique<TouchCommand>();
	}
	if (commandName == "wc") {
		return make_unique<WcCommand>();
	}
	if (commandName == "time") {
		return make_unique<TimeCommand>();
	}
	if (commandName == "date") {
		return make_unique<DateCommand>();
	}
	if (commandName == "prompt") {
		return make_unique<PromptCommand>();
	}
	if (commandName == "truncate") {
		return make_unique<TruncateCommand>();
	}
	if (commandName == "rm") {
		return make_unique<RmCommand>();
	}
	if (commandName == "tr") {
		return make_unique<TrCommand>();
	}
	if (commandName == "head") {
		return make_unique<HeadCommand>();
	}
	if (commandName == "batch") {
		return make_unique<BatchCommand>();
	}


	return nullptr;
}
