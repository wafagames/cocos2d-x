//
//  JsonUtil.hpp
//  cocos2d_libs
//
//  Created by joe on 2017/12/20.
//

#ifndef JsonUtil_hpp
#define JsonUtil_hpp

#include <stdio.h>
#include <string>
//#include "platform/CCPlatformMacros.h"
//#include "2d/CCNode.h"
//#include "cocos2d.h"

#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "json/rapidjson.h"
#include "platform/CCPlatformMacros.h"
#include "base/CCValue.h"
//#include "tinyxml2/tinyxml2.h"

namespace ccsp{
    class JsonUtil
    {
    public:
        static JsonUtil* getInstance();
        JsonUtil();
      
        std::string toString(cocos2d::ValueMap* valueMap);
        cocos2d::ValueMap toObj(const char* str);
        void print(rapidjson::Document* d);
    };
}

#endif /* JsonUtil_hpp */
