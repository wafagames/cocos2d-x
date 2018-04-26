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

#include "extensions/ccsp/jsb/define.h"

using namespace cocos2d;

namespace ccsp{
    namespace JSB{
        //namespace SpiderMonkey{
            class Util
            {
            public:
                static float toFloat (JSContext* cx, JS::CallArgs* args,int index);
                static int toInt32 (JSContext* cx, JS::CallArgs* args,int index);
                static bool toBool (JSContext* cx, JS::CallArgs* args,int index);
                static std::string toString (JSContext* cx, JS::CallArgs* args,int index);
                
                static Size toSize (JSContext* cx, JS::CallArgs* args,int index);
                static Point toPoint (JSContext* cx, JS::CallArgs* args,int index);
                static void* toObject(JSContext* cx, JS::CallArgs* args,int index);

                 static int returnInt8Array(JSContext* cx, JS::CallArgs* args,int index,void* memsrc,int size);
               
            };
        //}
    }
}

#endif
