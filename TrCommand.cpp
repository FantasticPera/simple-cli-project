#include "TrCommand.h"

using namespace std;

std::string TrCommand::execute(std::vector<std::string> commandVec)
{
	string arg;
	string what;
	string with = "";

	int inRedIndex = Command::findInRedIndex(commandVec);
	int outRedIndex = Command::findOutRedIndex(commandVec);

	if (inRedIndex != -1 and outRedIndex != -1 and commandVec.size() == 7) {
		with = readArgumentOrFile(commandVec[2]);
	}
	
	if (inRedIndex != -1) {
		arg = readArgumentOrFile(commandVec[inRedIndex + 1]);
		what = readArgumentOrFile(commandVec[1]);
		if (commandVec.size() == 5) {
			with = readArgumentOrFile(commandVec[2]);
		}
	}
	else if (commandVec.size() > 2){
		arg = readArgumentOrFile(commandVec[1]);
		what = readArgumentOrFile(commandVec[2]);
	}
	else {
		arg = MultilineReader::readMultiline();
		what = readArgumentOrFile(commandVec[1]);
	}

	if (outRedIndex != -1 and commandVec.size() == 6) {
		with = readArgumentOrFile(commandVec[3]);
	}

	else if (commandVec.size() == 4) {
		with = readArgumentOrFile(commandVec[3]);
	}
	
	for (int i = 0; i < arg.length(); i++) {
		char currChar = arg[i];

		if (currChar == what[0]) {
			
			if (arg.substr(i, what.length()) == what) {
				arg.erase(i, what.length());
				arg.insert(i, with);

				i += -1 + with.length();
			}
			
		}

	}


	if (outRedIndex != -1) {
		//ako fajl ne postoji
		if (!FileOperations::fileExists(commandVec[outRedIndex + 1])) {
			FileOperations::createFile(commandVec[outRedIndex + 1]);
		}

		if (commandVec[outRedIndex] == ">") {
			FileOperations::deleteFileContent(commandVec[outRedIndex + 1]);
		}

		FileOperations::writeFileContent(commandVec[outRedIndex + 1], arg);
		return "";

	}

	return arg;
	
}
