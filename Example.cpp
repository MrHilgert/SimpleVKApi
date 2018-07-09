// <shit>
#if defined(WIN32) && !defined(UNIX)
#define _CLEARCMD_ "clear"
#elif defined(UNIX) && !defined(WIN32)
#define _CLEARCMD_ "cls"
#else
#define _CLEARCMD_ "clear"
#endif
// </shit>

#include <algorithm>
#include "VKApi.h"

using namespace std;

CommandManager cm = CommandManager();

void onUpdate(struct VKLongPollUpdate update){
    printf("[%d/%s] %s\n", update.msgid, update.title.c_str(), update.body.c_str());

    string body = update.body;
    transform(body.begin(), body.end(), body.begin(), ::tolower);

    cm.call(update);
}

int main(int argc, char** argv){

    cm << (Command) { "привет", [](struct VKLongPollUpdate update){
        VK::messages::send(update.peerid, "Привет!", update.msgid);
    }};

    cm << (Command) { "пока", [](struct VKLongPollUpdate update){
        VK::messages::send(update.peerid, "Пока!", update.msgid);
    }};

    cm << (Command) { "как", [](struct VKLongPollUpdate update){
        if(update.body.compare("как меня зовут") == 0){

            VKRequest req("users.get");
            req << VK::auth::getAuth();

            req.param("user_ids", to_string(update.from));

            Document d = req.executeJson();

            Value& v = d["response"][0];

            string res("Тебя зовут ");

            res.append(v["first_name"].GetString()).append(" ");
            res.append(v["last_name"].GetString()).append("!");

            VK::messages::send(update.peerid, res, update.msgid);

        }
    }};

    cm << (Command) {"вложения", [](struct VKLongPollUpdate update){

        std::string res("Твои вложения:<br>");

        for(struct Attachment a : update.attachments)
            if(a.str.length() > 0) res.append(a.str).append("<br>");

        VK::messages::send(update.peerid, res, update.msgid);

    }};

    std::string user;
    std::string pass;

    cout << "Enter login: ";
    cin >> user;

    cout << "Enter pass: ";
    cin >> pass;

    VK::auth::authorize(user, pass);
    
    system(_CLEARCMD_);

    VK::LongPoll::startLPS(VK::messages::getLongPoll(), &onUpdate);
    return 0;
}
