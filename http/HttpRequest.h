#pragma once

#include <iostream>
#include <string.h>
#include <curl/curl.h>

#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

class HttpRequest {
    public:

    std::string url;
    std::string postfields;

    HttpRequest(std::string url){
        this->url = url;
    }

    std::string get(){
        std::string res;

        CURL* curl;
        CURLcode resp;

        curl = curl_easy_init();

        if(!curl) return "{\"error\":\"failed to initialize cURL\"}";

        std::string path = this->url.append("?").append(this->postfields);
        
        curl_easy_setopt(curl, CURLOPT_URL, path.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &res);
        
        resp = curl_easy_perform(curl);

        curl_easy_cleanup(curl);

        return res;
    }

    std::string post(){
        std::string res;

        CURL* curl;
        CURLcode resp;

        curl = curl_easy_init();

        if(!curl) return "{\"error\":\"failed to initialize cURL\"}";

        curl_easy_setopt(curl, CURLOPT_URL, this->url.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, this->postfields.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &res);
        
        resp = curl_easy_perform(curl);

        curl_easy_cleanup(curl);

        return res;
    }

    HttpRequest& param(std::string key, std::string value){
        this->postfields.append("&").append(key).append("=").append(value);
        return *this;
    }

    HttpRequest& operator << (std::string field) {
        this->postfields.append("&").append(field);
        return *this;
    }

    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp){
        ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
    }

};
#endif
