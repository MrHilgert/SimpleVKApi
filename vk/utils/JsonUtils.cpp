
#include <iostream>
#include <string.h>
#include "JsonUtils.h"
#include "rapidjson/document.h"

void VK::Utils::JSON::printJsonDocument(const rapidjson::Document *doc){
    rapidjson::StringBuffer sb;

    rapidjson::Writer<rapidjson::StringBuffer> writer(sb);
    
    (*doc).Accept(writer);

    std::cout << sb.GetString() << std::endl;
};

void VK::Utils::JSON::printJsonVal(const rapidjson::Value *val){
    rapidjson::StringBuffer sb;

    rapidjson::Writer<rapidjson::StringBuffer> writer(sb);
    
    (*val).Accept(writer);

    std::cout << sb.GetString() << std::endl;
};