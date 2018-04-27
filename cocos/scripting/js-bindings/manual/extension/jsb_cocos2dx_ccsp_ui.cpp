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
    
    if (argc != 6) {
        JS_ReportError(cx, "js_XPRichText_create : wrong number of arguments: %d, was expecting %d", argc, 6);
        return false;
    }
    
    float arg0=ccsp::JSB::Util::toFloat(cx,&args,0);
    Size arg1=ccsp::JSB::Util::toSize(cx,&args,1);
    TextHAlignment arg2=(TextHAlignment)ccsp::JSB::Util::toInt32(cx,&args,2);
    TextVAlignment arg3=(TextVAlignment)ccsp::JSB::Util::toInt32(cx,&args,3);
    int arg4=ccsp::JSB::Util::toInt32(cx,&args,4);
    bool arg5=ccsp::JSB::Util::toBool(cx,&args,5);
    
    auto ret = ccsp::XPRichText::create(arg0,arg1,arg2,arg3,arg4,arg5);

        //auto ret = ccsp::XPRichText::create(0,Size(0,0),TextHAlignment::LEFT,TextVAlignment::CENTER,0,false);
        js_type_class_t *typeClass = js_get_type_from_native<ccsp::XPRichText>(ret);
        JS::RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "ccsp::XPRichText"));
        args.rval().set(OBJECT_TO_JSVAL(jsret));
        return true;
    
    JS_ReportError(cx, "js_XPRichText_create : wrong number of arguments");
    return false;
}

static bool js_XPRichText_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    
    if (argc != 6) {
        JS_ReportError(cx, "js_XPRichText_ctor : wrong number of arguments: %d, was expecting %d", argc, 6);
        return false;
    }
    
    float arg0=ccsp::JSB::Util::toFloat(cx,&args,0);
    Size arg1=ccsp::JSB::Util::toSize(cx,&args,1);
    TextHAlignment arg2=(TextHAlignment)ccsp::JSB::Util::toInt32(cx,&args,2);
    TextVAlignment arg3=(TextVAlignment)ccsp::JSB::Util::toInt32(cx,&args,3);
    int arg4=ccsp::JSB::Util::toInt32(cx,&args,4);
    bool arg5=ccsp::JSB::Util::toBool(cx,&args,5);
    
    ccsp::XPRichText* nobj = new (std::nothrow) ccsp::XPRichText(arg0,arg1,arg2,arg3,arg4,arg5);
    
    //ccsp::XPRichText* nobj = new (std::nothrow) ccsp::XPRichText(0,Size(0,0),TextHAlignment::LEFT,TextVAlignment::CENTER,0,false);
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
    if (argc != 6) {
        JS_ReportError(cx, "js_XPRichText_constructor : wrong number of arguments: %d, was expecting %d", argc, 6);
        return false;
    }
    
    float arg0=ccsp::JSB::Util::toFloat(cx,&args,0);
    Size arg1=ccsp::JSB::Util::toSize(cx,&args,1);
    TextHAlignment arg2=(TextHAlignment)ccsp::JSB::Util::toInt32(cx,&args,2);
    TextVAlignment arg3=(TextVAlignment)ccsp::JSB::Util::toInt32(cx,&args,3);
    int arg4=ccsp::JSB::Util::toInt32(cx,&args,4);
    bool arg5=ccsp::JSB::Util::toBool(cx,&args,5);

    ccsp::XPRichText* cobj = new (std::nothrow) ccsp::XPRichText(arg0,arg1,arg2,arg3,arg4,arg5);

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
//        do {
//            if (args.get(0).isNull()) { arg0 = nullptr; break; }
//            if (!args.get(0).isObject()) { ok = false; break; }
//            js_proxy_t *jsProxy;
//            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
//            jsProxy = jsb_get_js_proxy(tmpObj);
//            arg0 = (cocos2d::ui::RichElement*)(jsProxy ? jsProxy->ptr : NULL);
//            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
//        } while (0);
        
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
         JS_FN("addClickEventForRenderer", js_XPRichText_addClickEventForRenderer, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
         JS_FN("setRenderString", js_XPRichText_setRenderString, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
         JS_FN("setRenderTexture", js_XPRichText_setRenderTexture, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
        
//        JS_FN("insertElement", js_cocos2dx_ui_RichText_insertElement, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
//        JS_FN("setAnchorTextOutline", js_cocos2dx_ui_RichText_setAnchorTextOutline, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
//        JS_FN("getFontSize", js_cocos2dx_ui_RichText_getFontSize, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
//        JS_FN("setAnchorTextBold", js_cocos2dx_ui_RichText_setAnchorTextBold, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
//        JS_FN("getAnchorFontColor", js_cocos2dx_ui_RichText_getAnchorFontColor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
//        JS_FN("getAnchorTextShadowBlurRadius", js_cocos2dx_ui_RichText_getAnchorTextShadowBlurRadius, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
//        JS_FN("setAnchorTextShadow", js_cocos2dx_ui_RichText_setAnchorTextShadow, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
//        JS_FN("isAnchorTextItalicEnabled", js_cocos2dx_ui_RichText_isAnchorTextItalicEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
//        JS_FN("setAnchorFontColor", js_cocos2dx_ui_RichText_setAnchorFontColor, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
//        JS_FN("setFontFace", js_cocos2dx_ui_RichText_setFontFace, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
//        JS_FN("setAnchorTextGlow", js_cocos2dx_ui_RichText_setAnchorTextGlow, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
//        JS_FN("setAnchorTextDel", js_cocos2dx_ui_RichText_setAnchorTextDel, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
//        JS_FN("getAnchorTextOutlineColor3B", js_cocos2dx_ui_RichText_getAnchorTextOutlineColor3B, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
//        JS_FN("stringWithColor4B", js_cocos2dx_ui_RichText_stringWithColor4B, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
//        JS_FN("initWithXML", js_cocos2dx_ui_RichText_initWithXML, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
//        JS_FN("getAnchorFontColor3B", js_cocos2dx_ui_RichText_getAnchorFontColor3B, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
//        JS_FN("formatText", js_cocos2dx_ui_RichText_formatText, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
//        JS_FN("getAnchorTextGlowColor3B", js_cocos2dx_ui_RichText_getAnchorTextGlowColor3B, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
//        JS_FN("openUrl", js_cocos2dx_ui_RichText_openUrl, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
//        JS_FN("getFontFace", js_cocos2dx_ui_RichText_getFontFace, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
//        JS_FN("setFontColor", js_cocos2dx_ui_RichText_setFontColor, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
//        JS_FN("isAnchorTextGlowEnabled", js_cocos2dx_ui_RichText_isAnchorTextGlowEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
//        JS_FN("getDefaults", js_cocos2dx_ui_RichText_getDefaults, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
//        JS_FN("isAnchorTextUnderlineEnabled", js_cocos2dx_ui_RichText_isAnchorTextUnderlineEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
//        JS_FN("getFontColor", js_cocos2dx_ui_RichText_getFontColor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
//        JS_FN("isAnchorTextShadowEnabled", js_cocos2dx_ui_RichText_isAnchorTextShadowEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
//        JS_FN("getAnchorTextOutlineSize", js_cocos2dx_ui_RichText_getAnchorTextOutlineSize, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
//        JS_FN("setVerticalSpace", js_cocos2dx_ui_RichText_setVerticalSpace, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
//        JS_FN("isAnchorTextDelEnabled", js_cocos2dx_ui_RichText_isAnchorTextDelEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
//        JS_FN("setDefaults", js_cocos2dx_ui_RichText_setDefaults, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
//        JS_FN("setWrapMode", js_cocos2dx_ui_RichText_setWrapMode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
//        JS_FN("setFontSize", js_cocos2dx_ui_RichText_setFontSize, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
//        JS_FN("removeElement", js_cocos2dx_ui_RichText_removeElement, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
//        JS_FN("setAnchorTextItalic", js_cocos2dx_ui_RichText_setAnchorTextItalic, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
//        JS_FN("getAnchorTextShadowOffset", js_cocos2dx_ui_RichText_getAnchorTextShadowOffset, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
//        JS_FN("isAnchorTextBoldEnabled", js_cocos2dx_ui_RichText_isAnchorTextBoldEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
//        JS_FN("getAnchorTextShadowColor3B", js_cocos2dx_ui_RichText_getAnchorTextShadowColor3B, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
//        JS_FN("stringWithColor3B", js_cocos2dx_ui_RichText_stringWithColor3B, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
//        JS_FN("isAnchorTextOutlineEnabled", js_cocos2dx_ui_RichText_isAnchorTextOutlineEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
//        JS_FN("getFontColor3B", js_cocos2dx_ui_RichText_getFontColor3B, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
//        JS_FN("getWrapMode", js_cocos2dx_ui_RichText_getWrapMode, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
//        JS_FN("setAnchorTextUnderline", js_cocos2dx_ui_RichText_setAnchorTextUnderline, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
//        JS_FN("color3BWithString", js_cocos2dx_ui_RichText_color3BWithString, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
       
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
    anonEvaluate(cx, global, "(function () { ccsp.ui.XPRichText.extend = cc.Class.extend; })()");
}
