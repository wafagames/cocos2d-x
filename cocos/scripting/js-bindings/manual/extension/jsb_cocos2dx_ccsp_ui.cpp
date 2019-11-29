//
//  jsb_cocos2dx_ccsp_ui.cpp
//  cocos2d_js_bindings
//
//  Created by joe on 2018/4/25.
//

//#include "jsb_cocos2dx_ccsp_ui.h"
#include "scripting/js-bindings/manual/extension/jsb_cocos2dx_ccsp.h"
#include "scripting/js-bindings/auto/jsb_cocos2dx_ui_auto.hpp"
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"
#include "ui/CocosGUI.h"
#include "extensions/ccsp/jsb/define.h"

template<class T>
static bool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS_ReportError(cx, "Constructor for the requested class is not available, please refer to the API reference.");
    return false;
}

static bool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    return false;
}

static bool js_is_native_obj(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    args.rval().setBoolean(true);
    return true;
}

JSClass  *jsb_XPRichText_class;
JSObject *jsb_XPRichText_prototype;

bool js_XPRichText_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    
    if (argc != 7) {
        JS_ReportError(cx, "js_XPRichText_create : wrong number of arguments: %d, was expecting %d", argc, 7);
        return false;
    }
    
    float arg0=ccsp::JSB::Util::toFloat(cx,&args,0);
    Size arg1=ccsp::JSB::Util::toSize(cx,&args,1);
    TextHAlignment arg2=(TextHAlignment)ccsp::JSB::Util::toInt32(cx,&args,2);
    TextVAlignment arg3=(TextVAlignment)ccsp::JSB::Util::toInt32(cx,&args,3);
    int arg4=ccsp::JSB::Util::toInt32(cx,&args,4);

    bool arg6=ccsp::JSB::Util::toBool(cx,&args,6);
    ccsp::XPRichText* ret = ccsp::XPRichText::create(arg0,arg1,arg2,arg3,arg4,nullptr,arg6);

    js_type_class_t *typeClass = js_get_type_from_native<ccsp::XPRichText>(ret);
    JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "ccsp::XPRichText"));
    args.rval().set(OBJECT_TO_JSVAL(jsret));
    return true;
}

static bool js_XPRichText_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    
    if (argc != 7) {
        JS_ReportError(cx, "js_XPRichText_ctor : wrong number of arguments: %d, was expecting %d", argc, 7);
        return false;
    }
    
    float arg0=ccsp::JSB::Util::toFloat(cx,&args,0);
    Size arg1=ccsp::JSB::Util::toSize(cx,&args,1);
    TextHAlignment arg2=(TextHAlignment)ccsp::JSB::Util::toInt32(cx,&args,2);
    TextVAlignment arg3=(TextVAlignment)ccsp::JSB::Util::toInt32(cx,&args,3);
    int arg4=ccsp::JSB::Util::toInt32(cx,&args,4);
    //std::function<void(Node*,Size)> arg5=ccsp::JSB::Util::toCallbackNodeSizeWithoutThis(cx,&args,5);
    bool arg6=ccsp::JSB::Util::toBool(cx,&args,6);
    
    ccsp::XPRichText* nobj = new (std::nothrow) ccsp::XPRichText(arg0,arg1,arg2,arg3,arg4,nullptr,arg6);
    
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    jsb_ref_init(cx, &p->obj, nobj, "ccsp::XPRichText");
    bool isFound = false;
    if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
    args.rval().setUndefined();
    return true;
}

bool js_XPRichText_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc != 7) {
        JS_ReportError(cx, "js_XPRichText_constructor : wrong number of arguments: %d, was expecting %d", argc, 7);
        return false;
    }
    
    float arg0=ccsp::JSB::Util::toFloat(cx,&args,0);
    Size arg1=ccsp::JSB::Util::toSize(cx,&args,1);
    TextHAlignment arg2=(TextHAlignment)ccsp::JSB::Util::toInt32(cx,&args,2);
    TextVAlignment arg3=(TextVAlignment)ccsp::JSB::Util::toInt32(cx,&args,3);
    int arg4=ccsp::JSB::Util::toInt32(cx,&args,4);
    //std::function<void(Node*,Size)> arg5=ccsp::JSB::Util::toCallbackNodeSizeWithoutThis(cx,&args,5);
    bool arg6=ccsp::JSB::Util::toBool(cx,&args,6);
    
    ccsp::XPRichText* cobj = new (std::nothrow) ccsp::XPRichText(arg0,arg1,arg2,arg3,arg4,nullptr,arg6);

    js_type_class_t *typeClass = js_get_type_from_native<ccsp::XPRichText>(cobj);
    // link the native object with the javascript object
    JS::RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "ccsp::XPRichText"));
    args.rval().set(OBJECT_TO_JSVAL(jsobj));
    if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
    return true;
}


bool js_XPRichText_pushBackElement(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    //bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ccsp::XPRichText* cobj = (ccsp::XPRichText *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_XPRichText_pushBackElement : Invalid Native Object");
    if (argc == 1) {
        cocos2d::ui::RichElement* arg0 = nullptr;
        arg0=(cocos2d::ui::RichElement*)ccsp::JSB::Util::toObject(cx,&args,0);
        if(arg0==nullptr){
            JS_ReportError(cx, "js_XPRichText_pushBackElement : Error processing arguments");
            return false;
        }
        //JSB_PRECONDITION2(ok, cx, false, "js_XPRichText_pushBackElement : Error processing arguments");
        cobj->pushBackElement(arg0);
        args.rval().setUndefined();
        return true;
    }
    
    JS_ReportError(cx, "js_XPRichText_pushBackElement : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}

bool js_XPRichText_getRenderByID(JSContext *cx, uint32_t argc, jsval *vp){
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 1) {
        int index=ccsp::JSB::Util::toInt32(cx,&args,0);
        if(index<0){
            JS_ReportError(cx, "js_XPRichText_getRenderByID : Error processing arguments");
            return false;
        }
        ccsp::XPRichText* cobj=(ccsp::XPRichText*)ccsp::JSB::Util::getThis(cx,&args);
        ccsp::JSB::Util::returnNode(cx,&args,cobj->getRenderByID(index));
        return true;
    }
    JS_ReportError(cx, "js_XPRichText_getRenderByID : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}

bool js_XPRichText_getRenderIndexByStr(JSContext *cx, uint32_t argc, jsval *vp){
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 1) {
        std::string s=ccsp::JSB::Util::toString(cx,&args,0);
        if(s.size()<=0){
            JS_ReportError(cx, "js_XPRichText_getRenderIndexByStr : Error processing arguments, give str is empty");
            return false;
        }
        ccsp::XPRichText* cobj=(ccsp::XPRichText*)ccsp::JSB::Util::getThis(cx,&args);
        ccsp::JSB::Util::returnInt(cx,&args,cobj->getRenderIndexByStr(s));
        return true;
    }
    JS_ReportError(cx, "js_XPRichText_getRenderIndexByStr : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}

bool js_XPRichText_setRenderString(JSContext *cx, uint32_t argc, jsval *vp){
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc >=2) {
        int index=ccsp::JSB::Util::toInt32(cx,&args,0);
        if(index<0){
            JS_ReportError(cx, "js_XPRichText_setRenderString : Error processing arguments");
            return false;
        }
        ccsp::XPRichText* richText=(ccsp::XPRichText*)ccsp::JSB::Util::getThis(cx,&args);
        std::string str=ccsp::JSB::Util::toString(cx,&args,1);
        Color4B color;
        if(argc==2){
            richText->setRenderString(index,str);
        }
        else if(argc==3){
            color=ccsp::JSB::Util::toColor4B(cx, &args,2);
            richText->setRenderString(index, str, color);
        }
        return true;
    }
    JS_ReportError(cx, "js_XPRichText_setRenderString : wrong number of arguments: %d, was expecting >=%d", argc, 2);
    return false;
}

bool js_XPRichText_setRenderTexture(JSContext *cx, uint32_t argc, jsval *vp){
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc ==2) {
        int index=ccsp::JSB::Util::toInt32(cx,&args,0);
        if(index<0){
            JS_ReportError(cx, "js_XPRichText_setRenderTexture : Error processing arguments");
            return false;
        }
        ccsp::XPRichText* richText=(ccsp::XPRichText*)ccsp::JSB::Util::getThis(cx,&args);
        std::string str=ccsp::JSB::Util::toString(cx,&args,1);
        richText->setRenderTexture(index, str);
        return true;
    }
    JS_ReportError(cx, "js_XPRichText_setRenderTexture : wrong number of arguments: %d, was expecting >=%d", argc, 2);
    return false;
}

bool js_XPRichText_setForceNewLine(JSContext *cx, uint32_t argc, jsval *vp){
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 1) {
        bool s=ccsp::JSB::Util::toBool(cx,&args,0);
        ccsp::XPRichText* cobj=(ccsp::XPRichText*)ccsp::JSB::Util::getThis(cx,&args);
        cobj->setForceNewLine(s);
        return true;
    }
    JS_ReportError(cx, "js_XPRichText_setForceNewLine : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}

bool js_XPRichText_addClickEventForRenderer(JSContext *cx, uint32_t argc, jsval *vp){
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc ==2) {
        int index=ccsp::JSB::Util::toInt32(cx,&args,0);
        if(index<0){
            JS_ReportError(cx, "js_XPRichText_addClickEventForRenderer : Error processing arguments");
            return false;
        }
        ccsp::XPRichText* richText=(ccsp::XPRichText*)ccsp::JSB::Util::getThis(cx,&args);
        std::string str=ccsp::JSB::Util::toString(cx,&args,1);
        std::function<void(cocos2d::Node*,Point)> callback=ccsp::JSB::Util::toCallbackNodePoint(cx, &args, 1);
        richText->addClickEventForRenderer(index, callback);
        return true;
    }
    JS_ReportError(cx, "js_XPRichText_addClickEventForRenderer : wrong number of arguments: %d, was expecting >=%d", argc, 2);
    return false;
}

bool js_XPRichText_setOnRenderEnd(JSContext *cx, uint32_t argc, jsval *vp){
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc ==1) {
        std::function<void(Node*,Size)> cb=ccsp::JSB::Util::toCallbackNodeSize(cx,&args,0);
        ccsp::XPRichText* richText=(ccsp::XPRichText*)ccsp::JSB::Util::getThis(cx,&args);
        richText->setOnRenrderEnd(cb);
        return true;
    }
    JS_ReportError(cx, "js_XPRichText_setOnRenderEnd : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}


extern JSObject *jsb_cocos2d_ui_Widget_prototype;

void js_register_XPRichText(JSContext *cx, JS::HandleObject global) {
    jsb_XPRichText_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_XPRichText_class->name = "XPRichText";
    jsb_XPRichText_class->addProperty = JS_PropertyStub;
    jsb_XPRichText_class->delProperty = JS_DeletePropertyStub;
    jsb_XPRichText_class->getProperty = JS_PropertyStub;
    jsb_XPRichText_class->setProperty = JS_StrictPropertyStub;
    jsb_XPRichText_class->enumerate = JS_EnumerateStub;
    jsb_XPRichText_class->resolve = JS_ResolveStub;
    jsb_XPRichText_class->convert = JS_ConvertStub;
    jsb_XPRichText_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);
    
    static JSPropertySpec properties[] = {
        JS_PS_END
    };
    
    static JSFunctionSpec funcs[] = {
         JS_FN("ctor", js_XPRichText_ctor, 6, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("pushBackElement", js_XPRichText_pushBackElement, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
         JS_FN("getRenderByID", js_XPRichText_getRenderByID, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getRenderIndexByStr", js_XPRichText_getRenderIndexByStr, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
         JS_FN("addClickEventForRenderer", js_XPRichText_addClickEventForRenderer, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
         JS_FN("setRenderString", js_XPRichText_setRenderString, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
         JS_FN("setRenderTexture", js_XPRichText_setRenderTexture, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setOnRenderEnd", js_XPRichText_setOnRenderEnd, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
         JS_FN("setForceNewLine", js_XPRichText_setForceNewLine, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };
    
    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_XPRichText_create, 6, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        //JS_FN("createWithXML", js_cocos2dx_ui_RichText_createWithXML, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };
    
    JS::RootedObject parent_proto(cx, jsb_cocos2d_ui_Widget_prototype);
    jsb_XPRichText_prototype = JS_InitClass(
                                                     cx, global,
                                                     parent_proto,
                                                     jsb_XPRichText_class,
                                                     js_XPRichText_constructor, 0, // constructor
                                                     properties,
                                                     funcs,
                                                     NULL, // no static properties
                                                     st_funcs);
    
    JS::RootedObject proto(cx, jsb_XPRichText_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "XPRichText"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::TrueHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<ccsp::XPRichText>(cx, jsb_XPRichText_class, proto, parent_proto);
    anonEvaluate(cx, global, "(function () { jsb.XPRichText.extend = cc.Class.extend; })()");
}
