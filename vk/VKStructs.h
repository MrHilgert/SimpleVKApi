
#pragma once

#include <iostream>
#include <string.h>

#ifndef VKSTRUCTS
#define VKSTRUCTS

struct VKParam {
    std::string key;
    std::string value;
};

struct VKChat {};

struct VKDialog : VKChat {
    int peerid;
    std::string title;
    VKMessage messages[];
    VKUser members[];
};

struct VKPrivateDialog : VKChat {
    VKUser peer;
    VKMessage messages[];
};

struct VKUser {
    int id;
    
    std::string first_name;
    std::string last_name;

    std::string domain;
};

struct VKMessage{
    int id;
    
    int sender;
    int peerid;
    
    long time;

    std::string body;

    bool unread;
};

struct VKLongpollSettingsResponse {
    std::string server;
    std::string key;
    long ts;
};

struct VKIntResult {
    int response;
};

struct VKMSGFlags {
    bool unread;
    bool outbox;
    bool replied;
    bool important;
    bool chat;
    bool friends;
    bool spam;
    bool deleted;
    bool fixed;
    bool media;
};

struct Attachment {
    std::string str;
};

struct VKLongPollUpdate {
    int msgid;
    
    struct VKMSGFlags flags;
    
    int peerid;
    
    long time;
    
    std::string title;
    std::string body;

    bool isChat;
    int from;

    struct Attachment attachments[10];
};


#endif