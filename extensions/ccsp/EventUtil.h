//
//  EventUtil.hpp
//  cocos2d_libs
//
//  Created by joe on 2017/12/19.
//

#ifndef EventUtil_hpp
#define EventUtil_hpp

#include <stdio.h>

#include <string>
#include "platform/CCPlatformMacros.h"
#include "ui/GUIExport.h"
#include "2d/CCNode.h"
#include "2d/CCActionInterval.h"
#include "base/CCEvent.h"

namespace  ccsp{
    class EventUtil{
    public:
        static EventUtil* getInstance();
        std::string  getUserDataAsJsonString(cocos2d::EventCustom* event);
    };
}

#endif /* EventUtil_hpp */
