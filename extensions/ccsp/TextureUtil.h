//
//  TextureHelper.hpp
//  cocos2d_libs
//
//  Created by joe on 2017/5/5.
//
//

#ifndef TextureUtil_h
#define TextureUtil_h

#include <stdio.h>

#include <stdio.h>
#include <string>

namespace ccsp{
    class TextureUtil
    {
    public:
        static TextureUtil* getInstance();
        void printPlistInfo();
        void printSpriteFramesInfo();
    };
}

#endif /* TextureUtil_h */
