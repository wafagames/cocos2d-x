//
//  DataUtil.cpp
//  cocos2d_libs
//
//  Created by joe on 2017/7/19.
//
//

#include "DataUtil.h"
#include "platform/CCFileUtils.h"


using namespace ccsp;
using namespace cocos2d;
static DataUtil* s_instance=NULL;

DataUtil* DataUtil::getInstance(){
    if(!s_instance){
        s_instance=new DataUtil();
    }
    return s_instance;
}

DataUtil::DataUtil(){
   
}

void DataUtil::store(const std::string &key,unsigned char* buf,int length){
    if(length<=0)
        return;
    unsigned char* newBuf=(unsigned char*)malloc(length);
    memcpy(newBuf,buf,length);
    unsigned char* oldBuf=_map_data[key];
    if(oldBuf){
        free(oldBuf);
    }
    _map_data[key]=newBuf;
    _map_len[key]=length;
}

unsigned char* DataUtil::getBuf(const std::string &key){
    return  _map_data[key];
}

int DataUtil::getLength(const std::string &key){
    return  _map_len[key];
}

void DataUtil::freeBuf(const std::string &key){
    unsigned char* oldBuf=_map_data[key];
    if(oldBuf){
        free(oldBuf);
        _map_data.erase(key);
        _map_len.erase(key);
    }
}
