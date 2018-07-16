//
//  JsonUtil.cpp
//  cocos2d_libs
//
//  Created by joe on 2017/12/20.
//

#include "JsonUtil.h"
#include "cocos/editor-support/cocostudio/DictionaryHelper.h"
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

void JsonUtil::print(rapidjson::Document* d){
    for (rapidjson::Value::ConstMemberIterator itr = d->MemberBegin(); itr != d->MemberEnd(); itr++)
    {
        rapidjson::Value jKey;
        rapidjson::Value jValue;
        rapidjson::Document::AllocatorType allocator;
        jKey.CopyFrom(itr->name, allocator);
        jValue.CopyFrom(itr->value,allocator);
        if (jKey.IsString())
        {
            std::string name = jKey.GetString();
            std::string value = jValue.GetString();
            CCLOG("%s : %s",name.c_str(),value.c_str());
        }
    }
}

std::string JsonUtil::toString(cocos2d::ValueMap* valueMap){
    rapidjson::Document d;
    d.SetObject();
    rapidjson::Document::AllocatorType& allocator=d.GetAllocator();
    //rapidjson::Value jsonObj(rapidjson::kObjectType);
    
    for(auto &i : *valueMap){
        const char* key=i.first.c_str();
        Value v=i.second;
        cocos2d::Value::Type t=v.getType();
        if(t==cocos2d::Value::Type::INTEGER){
            d.AddMember(rapidjson::StringRef(key),v.asInt(),allocator);
        }else if(t==cocos2d::Value::Type::UNSIGNED){
            d.AddMember(rapidjson::StringRef(key),v.asUnsignedInt(),allocator);
        }else if(t==cocos2d::Value::Type::FLOAT){
            d.AddMember(rapidjson::StringRef(key),v.asFloat(),allocator);
        }else if(t==cocos2d::Value::Type::DOUBLE){
            d.AddMember(rapidjson::StringRef(key),v.asDouble(),allocator);
        }else if(t==cocos2d::Value::Type::BOOLEAN){
            d.AddMember(rapidjson::StringRef(key),v.asBool(),allocator);
        }else if(t==cocos2d::Value::Type::STRING){
            rapidjson::Value jValue;
            jValue.SetString(v.asString().c_str(),allocator);
            d.AddMember(rapidjson::StringRef(key),jValue,allocator);
        }else{
            CCLOGERROR("JsonUtil::toString don't support key %s",key);
        }
    }
    
//    if(valueMap->size()>=3){
//        print(&d);
//    }
    
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    d.Accept(writer);
    //jsonObj.Accept(writer);
    const char* retStr= buffer.GetString();
    std::string s=retStr;
//    CCLOG("JsonUtil::toString %s",retStr);
    return s;
}

cocos2d::ValueMap JsonUtil::toObj(const char* str){
    rapidjson::Document doc;
    cocos2d::ValueMap retMap;
    doc.Parse(str);
    if (doc.HasParseError())
    {
        CCLOGERROR("GetParseError %d\n", doc.GetParseError());
        return retMap;
    }
    for (rapidjson::Value::ConstMemberIterator itr = doc.MemberBegin(); itr != doc.MemberEnd(); ++itr){
        //const char* type=itr->value.GetType();
        if(itr->value.IsString()){
            CCLOG("%s %s",itr->name.GetString(),itr->value.GetString());
            retMap[itr->name.GetString()]=cocos2d::Value(itr->value.GetString());
        }
        else if(itr->value.IsInt()){
             CCLOG("%s %d",itr->name.GetString(),itr->value.GetInt());
             retMap[itr->name.GetString()]=cocos2d::Value(itr->value.GetInt());
        }
        else if(itr->value.IsFloat()){
            CCLOG("%s %f",itr->name.GetString(),itr->value.GetFloat());
             retMap[itr->name.GetString()]=cocos2d::Value(itr->value.GetFloat());
        }
    }
//    for(auto &i : retMap){
//        CCLOG("%s %s",i.first.c_str(),i.second.asString().c_str());
//    }
    return retMap;
}
