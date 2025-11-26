#include "EchoCommand.h"

using namespace std;

string EchoCommand::execute(vector<string> commandVec) {
	//slucaj: ima argument
	if (commandVec.size() == 2) {
		string arg = commandVec[1];
		return Command::readArgumentOrFile(arg);
	}
	//slucaj ima redirekcije
	else if (commandVec.size() > 2) {
		int inRedIndex = Command::findInRedIndex(commandVec);
		int outRedIndex = Command::findOutRedIndex(commandVec);

		string arg;

		if (inRedIndex != -1) {
			FileOperations::readFile(commandVec[inRedIndex + 1], arg);
		}
		else{
			arg = Command::readArgumentOrFile(commandVec[1]);
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
	//slucaj: nema argument
	else {
		string arg = MultilineReader::readMultiline();
		return arg;
	}

}