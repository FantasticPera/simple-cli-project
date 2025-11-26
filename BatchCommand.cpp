#include "BatchCommand.h"

using namespace std;

std::string BatchCommand::execute(std::vector<std::string> commandVec)
{
    string arg;

    if (commandVec.size() >= 2) {
        int inRedIndex = Command::findInRedIndex(commandVec);
        

        if (inRedIndex != -1) {
            FileOperations::readFile(commandVec[inRedIndex + 1], arg);
        }
        else {
            arg = Command::readArgumentOrFile(commandVec[1]);
        }
    }
    else if (commandVec.size() == 1) {
        string arg = MultilineReader::readMultiline();
    }

    string finalBatchProduct;
    istringstream batchList(arg);
    string line;
    

    while (getline(batchList, line)) {
        int i = 0;
        Parser parser;
        parser.parse(line);

        vector<vector<string>> finalTokens = parser.getFinalTokens();

        if (!CommandChecker::checkCommands(finalTokens)) {
            finalBatchProduct += "Error: Invalid command in line - " + line + '\n';
            continue;
        }

        for (auto commandVec : finalTokens) {
            std::unique_ptr<Command> command = CommandVisitor::visitCommand(commandVec[0]);
            std::string result = command->execute(commandVec);
            if (i + 1 == finalTokens.size()) {
                if (result != "") {
                    finalBatchProduct += result + '\n';
                }
            }
            else {
                result = result + "\"";
                result = "\"" + result;

                if (finalTokens[i + 1][0] == "wc" or finalTokens[i + 1][0] == "head") {
                    finalTokens[i + 1].insert(finalTokens[i + 1].begin() + 2, result);
                }
                else {
                    finalTokens[i + 1].insert(finalTokens[i + 1].begin() + 1, result);
                }
            }
            i++;

        }


    }


    int outRedIndex = Command::findOutRedIndex(commandVec);
    if (outRedIndex != -1) {
        //if file does not exist
        if (!FileOperations::fileExists(commandVec[outRedIndex + 1])) {
            FileOperations::createFile(commandVec[outRedIndex + 1]);
        }

        if (commandVec[outRedIndex] == ">") {
            FileOperations::deleteFileContent(commandVec[outRedIndex + 1]);
        }

        FileOperations::writeFileContent(commandVec[outRedIndex + 1], finalBatchProduct);
        return "";

    }

    return finalBatchProduct;

}
