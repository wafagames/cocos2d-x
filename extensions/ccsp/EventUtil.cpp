//
//  EventUtil.cpp
//  cocos2d_libs
//
//  Created by joe on 2017/12/19.
//

#include "EventUtil.h"
#include <stdio.h>
#include "2d/CCActionInterval.h"
#include "base/CCEventCustom.h"
#include "JsonUtil.h"

using namespace ccsp;
using namespace cocos2d;
static EventUtil* s_instance=NULL;

EventUtil* EventUtil::getInstance(){
    if(!s_instance){
        s_instance=new EventUtil();
    }
    return s_instance;
}

//std::string getEventUserDataToString(cocos2d::Event* event);
std::string EventUtil::getUserDataAsJsonString(cocos2d::EventCustom* event){
    AnimationFrame::DisplayedEventInfo* dataInfo=(AnimationFrame::DisplayedEventInfo*)event->getUserData();
    std::string s=JsonUtil::getInstance()->toString((cocos2d::ValueMap*)dataInfo->userInfo);
    return s;
}
