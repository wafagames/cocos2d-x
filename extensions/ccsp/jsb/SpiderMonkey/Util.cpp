//
//  FileUtil.cpp
//  cocos2d_libs
//
//  Created by Joe on 2016/11/12.
//
//


#include "Util.h"
#include "cocos/scripting/js-bindings/manual/cocos2d_specifics.hpp"

using namespace cocos2d;
using namespace ccsp::JSB;

void* Util::getThis(JSContext *cx, JS::CallArgs *args){
    JS::RootedObject obj(cx, args->thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    if(!proxy)
        return NULL;
    return proxy->ptr;
}

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
        JS_ReportError(cx,"toPoint : jsval_to_ccpoint failed,arg index %d",index);
    
    return p;
}

Color4B  Util::toColor4B(JSContext* cx, JS::CallArgs* args,int index)
{
    Color4B color;
    if(!jsval_to_cccolor4b(cx, args->get(index), &color))
         JS_ReportError(cx,"toColor4B : jsval_to_cccolor4b failed,arg index %d",index);
    return color;
}

std::function<void(cocos2d::Node*,Point)> Util::toCallbackNodePoint(JSContext* cx,JS::CallArgs*args,int index){
        //std::function<void (cocos2d::Ref *)> callback=nullptr;
        if(JS_TypeOfValue(cx, args->get(index)) == JSTYPE_FUNCTION)
        {
            JS::RootedObject jstarget(cx, args->thisv().toObjectOrNull());
            std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, jstarget, args->get(index), args->thisv()));
            return [=](cocos2d::Node* sender,Point point) -> void {
                JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
                jsval largv[2];
                largv[0] = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::Node>(cx, (cocos2d::Node*)sender));
                const Vec2 p=Vec2(point.x,point.y);
                largv[1]=vector2_to_jsval(cx,p);
              
                JS::RootedValue rval(cx);
                bool succeed = func->invoke(2, &largv[0], &rval);
                if (!succeed && JS_IsExceptionPending(cx)) {
                    JS_ReportPendingException(cx);
                }
            };
        }
        return nullptr;
}


void Util::returnInt(JSContext* cx, JS::CallArgs* args,int v){
    args->rval().set(int32_to_jsval(cx,v));
}

void Util::returnString(JSContext* cx, JS::CallArgs* args,std::string& v){
    args->rval().set(std_string_to_jsval(cx,v));
}

void Util::returnCStr(JSContext* cx, JS::CallArgs* args,char* v){
    args->rval().set(c_string_to_jsval(cx,v));
}

void Util::returnNode(JSContext* cx, JS::CallArgs* args,Node* node){
    JS::RootedValue jsret(cx);
    if (node) {
        jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::Node>(cx, (cocos2d::Node*)node));
    } else {
        jsret = JSVAL_NULL;
    }
    args->rval().set(jsret);
}

void Util::returnPos(JSContext* cx, JS::CallArgs* args,Point v){
    args->rval().set(vector2_to_jsval(cx,v));
}

void Util::returnSize(JSContext* cx, JS::CallArgs* args,Size v){
    args->rval().set(ccsize_to_jsval(cx,v));
}

void Util::returnColor3B(JSContext* cx, JS::CallArgs* args,Color3B v){
    args->rval().set(cccolor3b_to_jsval(cx,v));
}

void Util::returnColor4B(JSContext* cx, JS::CallArgs* args,Color4B v){
    args->rval().set(cccolor4b_to_jsval(cx,v));
}

void Util::returnRect(JSContext* cx, JS::CallArgs* args,Rect v){
    args->rval().set(ccrect_to_jsval(cx,v));
}

int Util::returnUInt8Array(JSContext* cx, JS::CallArgs* args,int index,void* memsrc,int size){
    JS::RootedObject array(cx, JS_NewUint8Array(cx, size));
    if (nullptr == array)
        return 0;
    uint8_t* bufdata = (uint8_t*)JS_GetArrayBufferViewData(array);
    memcpy(bufdata, memsrc, size*sizeof(uint8_t));
    args->rval().set(OBJECT_TO_JSVAL(array));
    return size*sizeof(uint8_t);
}
int Util::returnInt8Array(JSContext* cx, JS::CallArgs* args,int index,void* memsrc,int size){
    JS::RootedObject array(cx, JS_NewInt8Array(cx, size));
    if (nullptr == array)
        return 0;
    int8_t* bufdata = (int8_t*)JS_GetArrayBufferViewData(array);
    memcpy(bufdata, memsrc, size*sizeof(int8_t));
    args->rval().set(OBJECT_TO_JSVAL(array));
    return size*sizeof(int8_t);
}

int Util::returnUInt16Array(JSContext* cx, JS::CallArgs* args,int index,void* memsrc,int size){
    JS::RootedObject array(cx, JS_NewUint16Array(cx, size));
    if (nullptr == array)
        return 0;
    uint16_t* bufdata = (uint16_t*)JS_GetArrayBufferViewData(array);
    memcpy(bufdata, memsrc, size*sizeof(uint16_t));
    args->rval().set(OBJECT_TO_JSVAL(array));
    return size*sizeof(uint16_t);
}
int Util::returnInt16Array(JSContext* cx, JS::CallArgs* args,int index,void* memsrc,int size){
    JS::RootedObject array(cx, JS_NewInt16Array(cx, size));
    if (nullptr == array)
        return 0;
    int16_t* bufdata = (int16_t*)JS_GetArrayBufferViewData(array);
    memcpy(bufdata, memsrc, size*sizeof(int16_t));
    args->rval().set(OBJECT_TO_JSVAL(array));
    return size*sizeof(int16_t);
}

int Util::returnUInt32Array(JSContext* cx, JS::CallArgs* args,int index,void* memsrc,int size){
    JS::RootedObject array(cx, JS_NewUint32Array(cx, size));
    if (nullptr == array)
        return 0;
    uint32_t* bufdata = (uint32_t*)JS_GetArrayBufferViewData(array);
    memcpy(bufdata, memsrc, size*sizeof(uint32_t));
    args->rval().set(OBJECT_TO_JSVAL(array));
    return size*sizeof(uint8_t);
}

int Util::returnInt32Array(JSContext* cx, JS::CallArgs* args,int index,void* memsrc,int size){
    JS::RootedObject array(cx, JS_NewInt32Array(cx, size));
    if (nullptr == array)
        return 0;
    int32_t* bufdata = (int32_t*)JS_GetArrayBufferViewData(array);
    memcpy(bufdata, memsrc, size*sizeof(int32_t));
    args->rval().set(OBJECT_TO_JSVAL(array));
    return size*sizeof(int32_t);
}
