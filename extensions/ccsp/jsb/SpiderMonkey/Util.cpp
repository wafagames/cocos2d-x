//
//  FileUtil.cpp
//  cocos2d_libs
//
//  Created by Joe on 2016/11/12.
//
//


#include "Util.h"
using namespace cocos2d;
using namespace ccsp::JSB;

int Util::toInt32 (JSContext* cx, JS::CallArgs* args,int index)
{
    int interval = 0;
    JS::RootedValue jsinterval(cx, args->get(index));
    if(JS::ToInt32(cx, jsinterval, &interval))
        return interval;
    return 0;
}

bool Util::toBool (JSContext* cx, JS::CallArgs* args,int index)
{
    return JS::ToBoolean(args->get(index));
}

float Util::toFloat (JSContext* cx, JS::CallArgs* args,int index)
{
    double interval = 0.0;
    JS::RootedValue jsinterval(cx, args->get(index));
    if(JS::ToNumber(cx, jsinterval, &interval))
        return (float)interval;
    return 0.0;
}
std::string Util::toString (JSContext* cx, JS::CallArgs* args,int index)
{
    std::string strRet;
    if(!jsval_to_std_string(cx, args->get(index), &strRet))
        return "";
    
    return strRet;
}

void* Util::toObject(JSContext *cx, JS::CallArgs *args, int index){
//    if (args.get(0).isNull()) { arg0 = nullptr; break; }
//    if (!args.get(0).isObject()) { ok = false; break; }
//    js_proxy_t *jsProxy;
//    JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
//    jsProxy = jsb_get_js_proxy(tmpObj);
//    arg0 = (cocos2d::ui::RichElement*)(jsProxy ? jsProxy->ptr : NULL);
    
    auto arg=args->get(0);
    js_proxy_t *jsProxy;
    if(arg.isNull() || !arg.isObject())
        return nullptr;
    JS::RootedObject tmpObj(cx, arg.toObjectOrNull());
    jsProxy = jsb_get_js_proxy(tmpObj);
    if(!jsProxy)
        return  nullptr;
    return jsProxy->ptr;
}

Size Util::toSize (JSContext* cx, JS::CallArgs* args,int index)
{
    Size size;
    if(!jsval_to_ccsize(cx, args->get(index), &size))
        return Size(0,0);
    
    return size;
}

Point Util::toPoint (JSContext* cx, JS::CallArgs* args,int index)
{
    Point p;
    if(!jsval_to_ccpoint(cx, args->get(index), &p))
        return Point(0,0);
    
    return p;
}

