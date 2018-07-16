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
#include "ui/CocosGUI.h"

namespace  ccsp{
    class UIUtil{
    public:
        static UIUtil* getInstance();
        cocos2d::Node* seekNodeByName(cocos2d::Node* root, const std::string& name);
        cocos2d::ui::Widget* seekWidgetByName(cocos2d::ui::Widget* root, const char* name);
         cocos2d::ui::Widget* seekWidgetByTag(cocos2d::ui::Widget* root, int tag);
    };
}

#endif /* UIUtil_hpp */
