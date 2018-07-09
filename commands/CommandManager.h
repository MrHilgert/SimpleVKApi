
#pragma once

#include <iostream>
#include <string.h>
#include <functional>
#include <map>

#include "../vk/VKStructs.h"

#ifndef CMDMANAGER_H
#define CMDMANAGER_H

struct Command {
    std::string name;
    std::function<void(VKLongPollUpdate)> callback;    
};

class CommandManager {

    public:

    std::map<std::string, struct Command> commands;

    CommandManager();
    ~CommandManager();

    void call(struct VKLongPollUpdate);

    void operator << (struct Command);

};

#endif