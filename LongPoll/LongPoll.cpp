#include "LongPoll.h"
#include "../vk/utils/JsonUtils.h"

void VK::LongPoll::startPolling(std::string server, std::string key, int64_t ts, void( * callbackFunction)(struct VKLongPollUpdate)) {

    long l_ts = ts;

    while (true) {
        HttpRequest req(server);

        req.param("act", "a_check").param("key", key).param("wait", "25").param("mode", std::to_string(2 & 8 & 64)).param("version", "0").param("ts", std::to_string(l_ts));

        std::string resp = req.get();

        rapidjson::Document d;

        d.Parse(resp.c_str());

        // StringBuffer sb;
        // Writer<StringBuffer> writer(sb);
        // d.Accept(writer);

        // std::cout << sb.GetString() << std::endl;

        if (d.HasMember("ts")) l_ts = d["ts"].GetInt64();

        if (d.HasMember("failed")) continue;

        for (const auto& i: d["updates"].GetArray()) {
            if (i[0] != 4) continue;
            
            VKLongPollUpdate upd;

            VKMSGFlags flags;

            VK::LongPoll::calculateMsgFlags(i[2].GetInt(), &flags);

            upd.msgid = i[1].GetInt();
            
            upd.flags = flags;
            
            upd.peerid = i[3].GetInt();

            upd.time = i[4].GetInt64();

            upd.title = i[5].GetString();
            upd.body = i[6].GetString();

            upd.isChat = upd.peerid > 2e9;
            upd.from = upd.peerid;

            if(i.Size() >= 8){

                if(i[7].HasMember("from")) upd.from = std::stoi(i[7]["from"].GetString());

                for(int index = 1; index <= 10; index++){
                    std::string memb;

                    memb.append("attach").append(std::to_string(index));

                    if(i[7].HasMember(memb.c_str())){

                        std::string type;
                        std::string val;

                        val = i[7][memb.c_str()].GetString();
                        
                        memb.append("_type");
                        type = i[7][memb.c_str()].GetString();

                        upd.attachments[index - 1] = (Attachment) {type.append(val)};
                    }
                }
            }

            if(upd.flags.outbox) upd.from = VK::auth::getSelf();

            callbackFunction(upd);

        }
        
    }

}

void VK::LongPoll::startLPS(struct VKLongpollSettingsResponse lps, void( * callbackFunction)(struct VKLongPollUpdate)) {
    VK::LongPoll::startPolling(lps.server, lps.key, lps.ts, callbackFunction);
}

void VK::LongPoll::calculateMsgFlags(int flag, struct VKMSGFlags *flags){
    (*flags).unread = (flag & 1) == 1;
    (*flags).outbox = (flag & 2) == 2;
    (*flags).replied = (flag & 4) == 4;
    (*flags).important = (flag & 8) == 8;
    (*flags).chat = (flag & 16) == 16;
    (*flags).friends = (flag & 32) == 32;
    (*flags).spam = (flag & 64) == 64;
    (*flags).deleted = (flag & 128) == 128;
    (*flags).fixed = (flag & 256) == 256;
    (*flags).media = (flag & 512) == 512;
}
