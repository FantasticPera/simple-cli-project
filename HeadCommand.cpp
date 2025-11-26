#include "HeadCommand.h"

using namespace std;

std::string HeadCommand::execute(std::vector<std::string> commandVec)
{
    int inRedIndex = Command::findInRedIndex(commandVec);
    int outRedIndex = Command::findOutRedIndex(commandVec);

    string option = commandVec[1];
    string arg;

    if (commandVec.size() == 2) {
        arg = MultilineReader::readMultiline();
    }
    else
    {
        if (inRedIndex != -1) {
            FileOperations::readFile(commandVec[inRedIndex + 1], arg);
        }
        else {
            arg = Command::readArgumentOrFile(commandVec[2]);
        }
    }



    istringstream text(arg);

    int nCount = stoi(option.substr(2));
    int lineCount = 0;



    string result;
    string line;

    while (getline(text, line) and lineCount < nCount) {
        if (lineCount > 0) {
            result += "\n";
        }
        result += line;
        lineCount++;
    }

    if (outRedIndex != -1) {
        //ako fajl ne postoji
        if (!FileOperations::fileExists(commandVec[outRedIndex + 1])) {
            FileOperations::createFile(commandVec[outRedIndex + 1]);
        }

        if (commandVec[outRedIndex] == ">") {
            FileOperations::deleteFileContent(commandVec[outRedIndex + 1]);
        }

        FileOperations::writeFileContent(commandVec[outRedIndex + 1], result);
        return "";

    }

    return result;


}
