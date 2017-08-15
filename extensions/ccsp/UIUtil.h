//
//  UIUtil.hpp
//  cocos2d_libs
//
//  Created by joe on 2017/8/15.
//
//

#ifndef UIUtil_h
#define UIUtil_h

#include <string>
#include "platform/CCPlatformMacros.h"
#include "ui/GUIExport.h"
#include "2d/CCNode.h"

namespace  ccsp{
    class UIUtil{
    public:
        static UIUtil* getInstance();
        cocos2d::Node* seekNodeByName(cocos2d::Node* root, const std::string& name);
    };
}

#endif /* UIUtil_hpp */
