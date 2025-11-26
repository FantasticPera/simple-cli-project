#include "Parser.h"
#include "CommandChecker.h"
#include "CommandMenager.h"
#include "CommandVisitor.h"
#include <iostream>

int main() {
    // Initialization of commands
    CommandManager::initialize();

    while (true) {
        
        std::string input;
        std::cout << CommandManager::getPromptSym();
        std::getline(std::cin, input);
        int i = 0; //counter for pipeline position

        
        Parser parser;
        parser.parse(input);

        
        std::vector<std::vector<std::string>> finalTokens = parser.getFinalTokens();

        // Commands validation
        if (!CommandChecker::checkCommands(finalTokens)) {
            continue;
        }
        else {
            

            for (auto commandVec : finalTokens) {
                std::unique_ptr<Command> command = CommandVisitor::visitCommand(commandVec[0]);
                std::string result = command->execute(commandVec);
                if (i + 1 == finalTokens.size()) {
                    if (result != "") {
                        //end of pipeline
                        std::cout << result << std::endl;
                    }
                }
                else {
                    //still in pipeline

                    result = result + "\"";
                    result = "\"" + result;

                    if (finalTokens[i+1][0] == "wc" or finalTokens[i+1][0] == "head") {
                        finalTokens[i + 1].insert(finalTokens[i + 1].begin() + 2, result);
                    }
                    else {
                        finalTokens[i + 1].insert(finalTokens[i + 1].begin() + 1, result);
                    }
                }
                i++;
                
            }
        }
        

    }

    return 0;
}
