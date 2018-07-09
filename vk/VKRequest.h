
#pragma once

#include "../http/HttpRequest.h"
#include "../vk/VKStructs.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"

#ifndef VKREQUEST_H_
#define VKREQUEST_H_

using namespace rapidjson;
using namespace std;

class VKRequest {

    private:
    string method;
    string params;

    public:
    VKRequest(string method){
        this->method = method;
        this->params = "v=5.80";
    }

    VKRequest& param(string key, string value){
        params.append("&").append(key).append("=").append(value);
        return *this;
    }

    // void operator << (string param){
    //     params.append("&").append(param);
    // }

    VKRequest& operator << (struct VKParam param){
        params.append("&").append(param.key).append("=").append(param.value);
        return *this;
    }

    string execute(){
        string str("https://api.vk.com/method/");
        
        str.append(this->method);

        HttpRequest req(str);
        req << this->params;

        return req.post();
    }

    Document executeJson(){
        Document d;

        std::string str = execute();

        d.Parse(str.c_str());
        
        return d;
    }

};

#endif