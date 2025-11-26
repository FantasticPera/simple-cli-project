#include "Command.h"

using namespace std;

string Command::readArgumentOrFile(string arg) {
	if (ArgumentChecker::checkArgument(arg) == 1) { // It's argument
		arg.erase(arg.size() - 1, 1);
		arg.erase(0, 1);
		return arg;
	}
	else if (ArgumentChecker::checkArgument(arg) == 0) { // it's file
		string result = "";
		if (FileOperations::readFile(arg, result)) {
			return result;
		}
		else return "";
	}
}

int Command::findInRedIndex(std::vector<std::string> commandVec) {
	auto inRed = std::find(commandVec.begin(), commandVec.end(), "<");
	if (inRed != commandVec.end()) {
		return inRed - commandVec.begin();
	}
	return -1;
}

int Command::findOutRedIndex(std::vector<std::string> commandVec) {
	auto outRed = std::find(commandVec.begin(), commandVec.end(), ">");
	if (outRed != commandVec.end()) {
		return outRed - commandVec.begin();
	}

	outRed = std::find(commandVec.begin(), commandVec.end(), ">>");
	if (outRed != commandVec.end()) {
		return outRed - commandVec.begin();
	}
	return -1;
}
