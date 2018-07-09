
#include "CommandManager.h"

CommandManager::CommandManager(){};
CommandManager::~CommandManager(){};

void CommandManager::operator<< (struct Command cmd) {
    this->commands[cmd.name] = cmd;
};

void CommandManager::call(struct VKLongPollUpdate update){
    std::string cmd = update.body.find(" ") != std::string::npos ? update.body.substr(0, update.body.find(" ")) : update.body;

    if(this->commands.find(cmd) == this->commands.end()) return;

    this->commands[cmd].callback(update);
};
