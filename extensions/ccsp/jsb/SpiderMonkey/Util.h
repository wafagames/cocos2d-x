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
                 static std::function<void(unsigned char*,int)> toInt322 (JSContext* cx, JS::CallArgs* args,int index);
                static bool toBool (JSContext* cx, JS::CallArgs* args,int index);
                static std::string toString (JSContext* cx, JS::CallArgs* args,int index);
                static void* toVoidMemoryFromUint8Array(JSContext* cx,JS::CallArgs* args,int index,int* size);
                static void* toVoidMemoryFromUint16Array(JSContext* cx,JS::CallArgs* args,int index,int* size);
                static void* toVoidMemoryFromUint32Array(JSContext* cx,JS::CallArgs* args,int index,int* size);
                static void* toVoidMemoryFromInt8Array(JSContext* cx,JS::CallArgs* args,int index,int* size);
                static void* toVoidMemoryFromInt16Array(JSContext* cx,JS::CallArgs* args,int index,int* size);
                static void* toVoidMemoryFromInt32Array(JSContext* cx,JS::CallArgs* args,int index,int* size);
                static void* toVoidMemoryFromFloat32Array(JSContext* cx,JS::CallArgs* args,int index,int* size);
                static void* toVoidMemoryFromFloat64Array(JSContext* cx,JS::CallArgs* args,int index,int* size);
                
                static Size toSize (JSContext* cx, JS::CallArgs* args,int index);
                static Point toPoint (JSContext* cx, JS::CallArgs* args,int index);
                static Color4B toColor4B (JSContext* cx, JS::CallArgs* args,int index);
                static void* toObject(JSContext* cx, JS::CallArgs* args,int index);
                static std::function<void(cocos2d::Node*,Point)> toCallbackNodePoint(JSContext* cx,JS::CallArgs*args,int index);
                static std::function<void(cocos2d::Node*,Size)> toCallbackNodeSize(JSContext* cx,JS::CallArgs*args,int index);
                static std::function<void(cocos2d::Node*,Size)> toCallbackNodeSize(JSContext* cx,JS::CallArgs*args,int index,JS::HandleValue thisObj);
                static std::function<void(cocos2d::Node*,Size)> toCallbackNodeSizeWithoutThis(JSContext* cx,JS::CallArgs*args,int index,JS::RootedObject jstarget);
                 static std::function<void(unsigned char*,int)> toCallbackBufSize(JSContext* cx,JS::CallArgs*args,int index);
                static void returnRect(JSContext* cx, JS::CallArgs* args,Rect v);
                static void returnInt(JSContext* cx, JS::CallArgs* args,int v);
                static void returnString(JSContext* cx, JS::CallArgs* args,std::string& v);
                static void returnCStr(JSContext* cx, JS::CallArgs* args,char* v);
                static void returnPos(JSContext* cx, JS::CallArgs* args,Point p);
                static void returnSize(JSContext* cx, JS::CallArgs* args,Size p);
                static void returnColor3B(JSContext* cx, JS::CallArgs* args,Color3B c);
                static void returnColor4B(JSContext* cx, JS::CallArgs* args,Color4B c);
                static void returnNode(JSContext* cx, JS::CallArgs* args,Node* node);
                static int returnInt8Array(JSContext* cx, JS::CallArgs* args,void* memsrc,int size);
                static int returnUInt8Array(JSContext* cx, JS::CallArgs* args,void* memsrc,int size);
                static int returnInt16Array(JSContext* cx, JS::CallArgs* args,void* memsrc,int size);
                static int returnUInt16Array(JSContext* cx, JS::CallArgs* args,void* memsrc,int size);
                static int returnInt32Array(JSContext* cx, JS::CallArgs* args,void* memsrc,int size);
                static int returnUInt32Array(JSContext* cx, JS::CallArgs* args,void* memsrc,int size);
                
                static int returnFloat32Array(JSContext* cx, JS::CallArgs* args,void* memsrc,int size);
                static int returnFloat64Array(JSContext* cx, JS::CallArgs* args,void* memsrc,int size);
            };
        //}
    }
}

#endif
