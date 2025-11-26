#include "RmCommand.h"

using namespace std;

std::string RmCommand::execute(std::vector<std::string> commandVec)
{
	int inRedIndex = Command::findInRedIndex(commandVec);
	string fileName;

	if (inRedIndex != -1) {
		FileOperations::readFile(commandVec[inRedIndex + 1], fileName);
	}
	else fileName = commandVec[1];

	if (ArgumentChecker::checkArgument(fileName) == 1) {
		fileName.erase(0, 1);
		fileName.erase(fileName.size() - 1, 1);
	}

	FileOperations::deleteFile(fileName);
	return "";
}
