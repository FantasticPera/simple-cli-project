#ifndef CommandMenager_h
#define CommandMenager_h

#include <string>
#include <unordered_map>

struct CommandFeatures {
    bool receives;
    bool sends;
    CommandFeatures() : receives(false), sends(false) {}
    CommandFeatures(bool receives, bool sends) : receives(receives), sends(sends) {}
};



class CommandManager {

public:
    static void initialize();
    static bool commandExists(std::string commandName);
    static CommandFeatures getCommandFeature(std::string commandName);
    static void setPromptSym(std::string arg);
    static std::string getPromptSym();

private:
    static std::unordered_map<std::string, CommandFeatures> commands;
    static std::string promptSym;
};

#endif

