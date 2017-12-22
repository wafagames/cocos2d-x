//
//  JsonUtil.cpp
//  cocos2d_libs
//
//  Created by joe on 2017/12/20.
//

#include "JsonUtil.h"
//#include "cocos2d.h"
using namespace ccsp;
using namespace cocos2d;
static JsonUtil* s_instance=NULL;

JsonUtil* JsonUtil::getInstance(){
    if(!s_instance){
        s_instance=new JsonUtil();
    }
    return s_instance;
}

JsonUtil::JsonUtil(){
    
}

std::string JsonUtil::toString(cocos2d::ValueMap* valueMap){
    rapidjson::Document d;
    d.SetObject();
    rapidjson::Document::AllocatorType& allocator=d.GetAllocator();
    rapidjson::Value jsonObj(rapidjson::kObjectType);
    
    for(auto &i : *valueMap){
        const char* key=i.first.c_str();
        Value v=i.second;
        cocos2d::Value::Type t=v.getType();
        if(t==cocos2d::Value::Type::INTEGER){
            jsonObj.AddMember(rapidjson::StringRef(key),v.asInt(),allocator);
        }else if(t==cocos2d::Value::Type::UNSIGNED){
            jsonObj.AddMember(rapidjson::StringRef(key),v.asUnsignedInt(),allocator);
        }else if(t==cocos2d::Value::Type::FLOAT){
            jsonObj.AddMember(rapidjson::StringRef(key),v.asFloat(),allocator);
        }else if(t==cocos2d::Value::Type::DOUBLE){
            jsonObj.AddMember(rapidjson::StringRef(key),v.asDouble(),allocator);
        }else if(t==cocos2d::Value::Type::BOOLEAN){
            jsonObj.AddMember(rapidjson::StringRef(key),v.asBool(),allocator);
        }else if(t==cocos2d::Value::Type::STRING){
            jsonObj.AddMember(rapidjson::StringRef(key),rapidjson::StringRef(v.asString().c_str()),allocator);
        }else{
            CCLOGERROR("JsonUtil::toString don't support key %s",key);
        }
    }
    //d.AddMember(jsonObj,allocator);
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
//    d.Accept(writer);
    jsonObj.Accept(writer);
    const char* retStr= buffer.GetString();
    std::string s=retStr;
//    CCLOG("JsonUtil::toString %s",retStr);
    return s;
}
