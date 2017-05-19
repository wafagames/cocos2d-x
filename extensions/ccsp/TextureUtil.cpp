//
//  TextureHelper.cpp
//  cocos2d_libs
//
//  Created by joe on 2017/5/5.
//
//

#include "TextureUtil.h"
#include "cocos2d.h"

using namespace ccsp;
using namespace cocos2d;
static TextureUtil* s_instance=NULL;

TextureUtil* TextureUtil::getInstance(){
    if(!s_instance){
        s_instance=new TextureUtil();
    }
    return s_instance;
}

void TextureUtil::printPlistInfo(){
    for(auto & i :  *SpriteFrameCache::getInstance()->_loadedFileNames){
        CCLOG("TextureUtil:plist file %s",i.c_str());
    }
}

void TextureUtil::printSpriteFramesInfo(){
    for(auto& i : SpriteFrameCache::getInstance()->_spriteFrames){
        CCLOG("TextureUtil:sprite frame %s",i.first.c_str());
    }
}
