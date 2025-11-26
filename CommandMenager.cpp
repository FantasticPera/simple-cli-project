#include "CommandMenager.h"

std::unordered_map<std::string, CommandFeatures> CommandManager::commands;
std::string CommandManager::promptSym = "$";

void CommandManager::initialize() {
    // Adding command features here, (recieves, sends)
    commands["echo"] = CommandFeatures(true, true);
    commands["touch"] = CommandFeatures(true, false);
    commands["date"] = CommandFeatures(false, true);
    commands["time"] = CommandFeatures(false, true);
    commands["tr"] = CommandFeatures(true, true);
    commands["wc"] = CommandFeatures(true, true);
    commands["rm"] = CommandFeatures(true, false);
    commands["truncate"] = CommandFeatures(true, false);
    commands["head"] = CommandFeatures(true, true);
    commands["prompt"] = CommandFeatures(true, false);
    commands["batch"] = CommandFeatures(true, true);
    

}

bool CommandManager::commandExists(std::string commandName) {
    return commands.find(commandName) != commands.end();
}

CommandFeatures CommandManager::getCommandFeature(std::string commandName) {
    return commands[commandName];
}

void CommandManager::setPromptSym(std::string arg)
{
    promptSym = arg;
}

std::string CommandManager::getPromptSym()
{
    return promptSym;
}

