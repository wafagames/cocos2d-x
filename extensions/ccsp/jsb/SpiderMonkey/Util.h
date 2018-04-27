//
//  FileUtil.hpp
//  cocos2d_libs
//
//  Created by Joe on 2016/11/12.
//
//

#ifndef ccsp_JSB_SpirderMoneky_Util_h
#define ccsp_JSB_SpirderMoneky_Util_h

#include <stdio.h>
#include <string>
#include <functional>
#include "extensions/ccsp/jsb/define.h"

using namespace cocos2d;

namespace ccsp{
    namespace JSB{
        //namespace SpiderMonkey{
            class Util
            {
            public:
                static void* getThis(JSContext* cx, JS::CallArgs* args);
                
                static float toFloat (JSContext* cx, JS::CallArgs* args,int index);
                static int toInt32 (JSContext* cx, JS::CallArgs* args,int index);
                static bool toBool (JSContext* cx, JS::CallArgs* args,int index);
                static std::string toString (JSContext* cx, JS::CallArgs* args,int index);
                
                static Size toSize (JSContext* cx, JS::CallArgs* args,int index);
                static Point toPoint (JSContext* cx, JS::CallArgs* args,int index);
                static Color4B toColor4B (JSContext* cx, JS::CallArgs* args,int index);
                static void* toObject(JSContext* cx, JS::CallArgs* args,int index);
                static std::function<void(cocos2d::Node*,Point)> toCallbackNodePoint(JSContext* cx,JS::CallArgs*args,int index);
                
                static void returnNode(JSContext* cx, JS::CallArgs* args,Node* node);
                static int returnInt8Array(JSContext* cx, JS::CallArgs* args,int index,void* memsrc,int size);
               
            };
        //}
    }
}

#endif
