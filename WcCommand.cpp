#include "WcCommand.h"

using namespace std;

string WcCommand::execute(vector<string> commandVec) {
	//no redirection
	if (commandVec.size() == 3) {
		string arg;
		arg = Command::readArgumentOrFile(commandVec[2]);
		return countWC(arg, commandVec[1]);
	}

	//has redirection
	if (commandVec.size() > 3) {

		int inRedIndex = Command::findInRedIndex(commandVec);
		int outRedIndex = Command::findOutRedIndex(commandVec);

		string arg;

		if (inRedIndex != -1) {
			FileOperations::readFile(commandVec[inRedIndex + 1], arg);
		}
		else {
			arg = Command::readArgumentOrFile(commandVec[2]);
		}

		if (outRedIndex != -1) {
			
			if (!FileOperations::fileExists(commandVec[outRedIndex + 1])) {
				FileOperations::createFile(commandVec[outRedIndex + 1]);
			}

			if (commandVec[outRedIndex] == ">") {
				FileOperations::deleteFileContent(commandVec[outRedIndex + 1]);
			}

			FileOperations::writeFileContent(commandVec[outRedIndex + 1], countWC(arg, commandVec[1]));
			return "";

		}

		return countWC(arg, commandVec[1]);
	}

	// no argument case
	else {
		string arg = MultilineReader::readMultiline();
		return countWC(arg, commandVec[1]);
	}

}


string WcCommand::countWC(string arg, string option) {
	if (arg == "") return "";
	int counter = 0;
	if (option == "-w") {
		istringstream text(arg);
		string word;
		while (text >> word) {
			counter++;
		}
		return to_string(counter);
	}
	else if (option == "-c") {
		counter = arg.size();
		return to_string(counter);
	}
}