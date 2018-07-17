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
#include <functional>
#include "platform/CCPlatformMacros.h"
#include "ui/GUIExport.h"
#include "2d/CCNode.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;

namespace  ccsp{
    class UIUtil{
    public:
        static UIUtil* getInstance();
        Node* seekNodeByName(Node* root, const std::string& name);
        static cocos2d::ui::Widget* seekWidgetByName(cocos2d::ui::Widget* root, const char* name);
        static cocos2d::ui::Widget* seekWidgetByTag(cocos2d::ui::Widget* root, int tag);
        static cocos2d::ui::ImageView* createImage(const char* szPath,Vec2 pos,bool scale9Enabled,int s_w,int s_h);
        static cocos2d::ui::Button* createBtn(const char* szPath,const char* str,Color3B c,const char* fontName,
                                              int fontSize,bool scale9Enabled,int s_w,int s_h,Size size,Vec2 pos,
                                              std::function<void(Ref*)>,bool bHide);
    };
}

#endif /* UIUtil_hpp */
