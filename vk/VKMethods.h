
#pragma once

#include "VKStructs.h"
#include "VKRequest.h"

#ifndef VKMETHODS_H_
#define VKMETHODS_H_

namespace VK {

    namespace auth {
        VKParam authorize(string username, string password);
        VKParam getAuth();
        int getSelf();
        bool checkAuth();
    }; // auth

    namespace messages {
        VKIntResult send(int peer_id, string message, int forward_message);
        VKLongpollSettingsResponse getLongPoll();
        VKChat getHistory(int peer_id, int messages_count, int offset = 0);
    }; // messages

} // VK

#endif