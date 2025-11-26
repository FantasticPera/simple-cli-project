#include "DateCommand.h"

using namespace std;

string DateCommand::execute(vector<std::string> commandVec) {
	ostringstream result;
	time_t t = time(nullptr);
	tm tm;
	localtime_s(&tm, &t);
	result << put_time(&tm, "%Y/%m/%d");
	int outRedIndex = Command::findOutRedIndex(commandVec);

	if (outRedIndex != -1) {
		//ako fajl ne postoji
		if (!FileOperations::fileExists(commandVec[outRedIndex + 1])) {
			FileOperations::createFile(commandVec[outRedIndex + 1]);
		}

		if (commandVec[outRedIndex] == ">") {
			FileOperations::deleteFileContent(commandVec[outRedIndex + 1]);
		}

		FileOperations::writeFileContent(commandVec[outRedIndex + 1], result.str());
		return "";

	}
	return result.str();
}
