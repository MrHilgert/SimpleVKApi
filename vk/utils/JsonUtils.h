
#pragma once

#include <iostream>
#include <string.h>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"

namespace VK {

    namespace Utils {

        namespace JSON {

            void printJsonDocument(const Document *doc);
            
            void printJsonVal(const rapidjson::Value *val);

        }

    }

}