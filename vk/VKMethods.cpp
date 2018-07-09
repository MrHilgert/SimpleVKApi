#include <rapidjson/rapidjson.h>
#include <rapidjson/writer.h>
#include "VKMethods.h"

namespace VK{
    namespace auth{
        int selfId;
        VKParam _auth;
    }
}

VKParam VK::auth::authorize(std::string username, std::string password) {
    HttpRequest req("https://oauth.vk.com/token");

    req.param("grant_type", "password");
    req.param("client_id", "3697615").param("client_secret", "AlVXZFMUqyrnABp8ncuU");
    req.param("username", username).param("password", password);
    req.param("scope", "all");

    Document d;
    d.Parse(req.get().c_str());

    VK::auth::selfId = d["user_id"].GetInt();

    return VK::auth::_auth = (VKParam) {
        "access_token",
        d["access_token"].GetString()
    };

}

VKParam VK::auth::getAuth() {
    return VK::auth::_auth;
}

int VK::auth::getSelf(){
    return VK::auth::selfId;
}

VKIntResult VK::messages::send(int peer_id, std::string message, int forward_message = -1) {
    VKRequest req("messages.send");
    req.param("peer_id", to_string(peer_id)).param("message", message) << auth::getAuth();

    if (forward_message > 0) req.param("forward_messages", to_string(forward_message));

    Document d = req.executeJson();

    return {
        d["response"].GetInt()
    };
}

VKLongpollSettingsResponse VK::messages::getLongPoll() {
    struct VKLongpollSettingsResponse resp;

    VKRequest req("messages.getLongPollServer");

    req.param("lp_version", "2") << auth::getAuth();

    Document d = req.executeJson();

    Value & val = d["response"];

    string server = string(val["server"].GetString());

    string key = string(val["key"].GetString());

    long ts = val["ts"].GetUint();

    resp.server.append("https://").append(server);
    resp.key = key;
    resp.ts = ts;

    return resp;
}

/*
VKChat VK::messages::getHistory(int peer_id, int messages_count = 100, int offset = 0){
    VKChat c;
    
    VKRequest req("messages.getHistory");

    req.param("peer_id", to_string(peer_id)).param("count", to_string(messages_count)).param("offset", to_string(offset)) << auth::getAuth();

    Document d = req.executeJson();

    Value& response = d["response"];

    if(peer_id > 2e9){
        c = (VKDialog) {};
    }else{
        c = (VKPrivateDialog) {};
    }


    
    return c;
}
*/
