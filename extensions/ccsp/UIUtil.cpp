//
//  UIUtil.cpp
//  cocos2d_libs
//
//  Created by joe on 2017/8/15.
//
//



#include <stdio.h>
#include "UIUtil.h"


using namespace ccsp;
using namespace cocos2d;
static UIUtil* s_instance=NULL;

UIUtil* UIUtil::getInstance(){
    if(!s_instance){
        s_instance=new UIUtil();
    }
    return s_instance;
}
Node* UIUtil::seekNodeByName(Node* root, const std::string& name)
{
    if (!root)
    {
        return nullptr;
    }
    if (root->getName() == name)
    {
        return root;
    }
    const auto& arrayRootChildren = root->getChildren();
    for (auto& subWidget : arrayRootChildren)
    {
        Node* child = dynamic_cast<Node*>(subWidget);
        if (child)
        {
            Node* res = seekNodeByName(child,name);
            if (res != nullptr)
            {
                return res;
            }
        }
    }
    return nullptr;
}
ui::Widget* UIUtil::seekWidgetByName(ui::Widget* root, const char* name){
        return cocos2d::ui::Helper::seekWidgetByName(root, name);
}
ui::Widget* UIUtil::seekWidgetByTag(ui::Widget* root, int tag){
    return cocos2d::ui::Helper::seekWidgetByTag(root, tag);
}


cocos2d::ui::ImageView* UIUtil::createImage(const char* szPath,Vec2 pos,bool scale9Enabled,int s_w,int s_h,Size s){
    ui::ImageView* image;
    if(szPath[0]=='#')
        image=ui::ImageView::create(&szPath[1],ui::Widget::TextureResType::PLIST);
    else
         image=ui::ImageView::create(szPath,ui::Widget::TextureResType::LOCAL);
    image->setIgnoreAnchorPointForPosition(false);
    image->setAnchorPoint(Point(0.5,0.5));
    image->setPosition(pos);
    if(scale9Enabled)
        image->setScale9Enabled(true);
    if(s_w || s_h){
        Size imgSize=image->getContentSize();
        image->setCapInsets(Rect(s_w,s_h,imgSize.width-s_w*2,imgSize.height-s_h*2));
    }
    if(s.width && s.height)
        image->setContentSize(s);
    return image;
}

cocos2d::ui::Button* UIUtil::createBtn(const char* szPath,const char* str,Color3B c,const char* fontName,
                                      int fontSize,bool scale9Enabled,int s_w,int s_h,Size size,Vec2 pos,
                                       std::function<void(Ref*)> cb,bool bHide){
    ui::Button* btnObj;
    if(szPath[0]=='#')
        btnObj=ui::Button::create(&szPath[1],&szPath[1],&szPath[1],ui::Widget::TextureResType::PLIST);
    else
        btnObj=ui::Button::create(szPath,szPath,szPath,ui::Widget::TextureResType::LOCAL);
    if(strlen(str))
        btnObj->setTitleText(str);
    btnObj->setTitleColor(c);
    if(strlen(fontName))
        btnObj->setTitleFontName(fontName);
    if(fontSize)
        btnObj->setTitleFontSize(fontSize);
    if(scale9Enabled && (s_w || s_h)){
        btnObj->setScale9Enabled(true);
        if(s_w || s_h){
            Size imgSize=btnObj->getContentSize();
            btnObj->setCapInsets(Rect(s_w,s_h,imgSize.width-s_w*2,imgSize.height-s_h*2));
        }
    }
    btnObj->setContentSize(size);
    btnObj->setPosition(pos);
    btnObj->addClickEventListener(cb);
    btnObj->setTouchEnabled(true);
    btnObj->setEnabled(true);
    btnObj->setIgnoreAnchorPointForPosition(false);
    btnObj->setAnchorPoint(Point(0.5,0.5));
    btnObj->setPressedActionEnabled(true);
    if(bHide)
        btnObj->setVisible(false);
    return btnObj;
}

cocos2d::ui::Text* UIUtil::createText(const char* str,Color4B c4,const char* fontName,
                                             int fontSize,TextHAlignment hAlign,Vec2 p){
    ui::Text* text=ui::Text::create(str, fontName, fontSize);
    text->setTextHorizontalAlignment(hAlign);
    text->setPosition(p);
    text->setTextColor(c4);
    text->setIgnoreAnchorPointForPosition(false);
    text->setAnchorPoint(Point(0.5,0.5));
    return text;
}

cocos2d::ui::LoadingBar* UIUtil::createBar(const char* szPath,float p,bool scale9Enabled,int s_w,int s_h,Size s,Vec2 pos){
    ui::LoadingBar* obj;
    if(szPath[0]=='#')
        obj=ui::LoadingBar::create(&szPath[1], ui::Widget::TextureResType::PLIST);
    else
        obj=ui::LoadingBar::create(szPath,ui::Widget::TextureResType::LOCAL);
    obj->setIgnoreAnchorPointForPosition(false);
    obj->setAnchorPoint(Point(0.5,0.5));
    obj->setContentSize(s);
    obj->setPosition(pos);
    if(scale9Enabled && (s_w || s_h)){
        obj->setScale9Enabled(true);
        if(s_w || s_h){
            Size imgSize=obj->getVirtualRendererSize();
            obj->setCapInsets(Rect(s_w,s_h,imgSize.width-s_w*2,imgSize.height-s_h*2));
        }
    }
   
    obj->setPercent(p);
    return obj;
}
