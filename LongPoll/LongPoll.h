
#pragma once

#include <iostream>
#include <string.h>
#include "../vk/VKMethods.h"

#ifndef LONGPOLL_H_
#define LONGPOLL_H_

namespace VK {
    namespace LongPoll {
        void startPolling(std::string server, std::string key, int64_t ts, void (*callbackFunction)(struct VKLongPollUpdate));
        void startLPS(struct VKLongpollSettingsResponse lps, void (*callbackFunction)(struct VKLongPollUpdate));
        void calculateMsgFlags(int flag, struct VKMSGFlags *flags);
    }; // #namespace LongPoll
}; // #namespace VK

#endif