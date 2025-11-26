#include "PromptCommand.h"

using namespace std;

std::string PromptCommand::execute(std::vector<std::string> commandVec)
{

	if (commandVec.size() == 2) {
		string arg = Command::readArgumentOrFile(commandVec[1]);
		CommandManager::setPromptSym(arg);
	}
	return "";
}