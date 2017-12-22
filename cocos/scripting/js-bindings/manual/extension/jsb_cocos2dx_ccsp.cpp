//
//  jsb_cocos2dx_ccsp.cpp
//  cocos2d_js_bindings
//
//  Created by Joe on 16/2/25.
//
//



#include "scripting/js-bindings/manual/extension/jsb_cocos2dx_ccsp.h"
#include "extensions/cocos-ext.h"
#include "scripting/js-bindings/manual/ScriptingCore.h"
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"
//#include "scripting/js-bindings/manual/jsb_cocos2dx_auto.hpp"
#include "scripting/js-bindings/auto/jsb_cocos2dx_auto.hpp"
//#include <thread>


USING_NS_CC;
USING_NS_CC_EXT;

bool js_copy_file(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    if (argc == 2)
    {
        std::string srcFileName;
        std::string dstFileName;
        bool ok = jsval_to_std_string(cx, args.get(0), &srcFileName);
        JSB_PRECONDITION2(ok, cx, false, "js_copy_file : Error processing arguments");
        
        ok = jsval_to_std_string(cx, args.get(1), &dstFileName);
        JSB_PRECONDITION2(ok, cx, false, "js_copy_file : Error processing arguments");
        
        bool ret=ccsp::FileUtil::getInstance()->copyFile(srcFileName, dstFileName);
        jsval jsret = JSVAL_NULL;
        jsret = INT_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    
    JS_ReportError(cx, "js_copy_file : wrong number of arguments");
    return false;
}

bool js_enableLogToFile(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    if (argc == 1)
    {
        int bEnable;
        bool ok = jsval_to_int(cx, args.get(0), &bEnable);
        JSB_PRECONDITION2(ok, cx, false, "js_enableLogToFile : Error processing arguments");
        ccsp::LogUtil::getInstance()->enableLogToFile(bEnable);
        return true;
    }
    JS_ReportError(cx, "js_enableLogToFile : wrong number of arguments");
    return false;
}

bool js_setLogFileFullName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    if (argc == 1)
    {
        std::string logFileName;
        bool ok = jsval_to_std_string(cx, args.get(0), &logFileName);
        JSB_PRECONDITION2(ok, cx, false, "js_setLogFileFullName : Error processing arguments");
        ccsp::LogUtil::getInstance()->setLogFileFullName(logFileName.c_str());
        return true;
    }
    JS_ReportError(cx, "js_setLogFileFullName : wrong number of arguments");
    return false;
}


bool js_setConnectTimeOut(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    if (argc == 1){
        int timeoutInSec;
        bool ok = jsval_to_int(cx, args.get(0), &timeoutInSec);
        JSB_PRECONDITION2(ok, cx, false, "js_setConnectTimeOut : Error processing arguments");
        //HttpMgr::getInstance()->setConnectTimeOut(cx, obj, timeout);
        cocos2d::network::HttpClient::getInstance()->setTimeoutForConnect(timeoutInSec);
        return  true;
    }
    JS_ReportError(cx, "js_setConnectTimeOut : wrong number of arguments");
    return  false;
}

bool js_setReadTimeOut(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    if (argc == 1){
        int timeoutInSec;
        bool ok = jsval_to_int(cx, args.get(0), &timeoutInSec);
        JSB_PRECONDITION2(ok, cx, false, "js_setReadTimeOut : Error processing arguments");
        //HttpMgr::getInstance()->setReadTimeOut(cx, obj, timeout);
        cocos2d::network::HttpClient::getInstance()->setTimeoutForRead(timeoutInSec);
        return true;
    }
    JS_ReportError(cx, "js_setReadTimeOut : wrong number of arguments");
    return  false;
}

bool js_unzip_to_path(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    if (argc == 3)
    {
        std::string zipFileName;
        std::string unzipPath;
        std::string password;
        bool ok = jsval_to_std_string(cx, args.get(0), &zipFileName);
        JSB_PRECONDITION2(ok, cx, false, "js_unzip_to_path : Error processing arguments");
        
        ok = jsval_to_std_string(cx, args.get(1), &unzipPath);
        JSB_PRECONDITION2(ok, cx, false, "js_unzip_to_path : Error processing arguments");
        
        ok = jsval_to_std_string(cx, args.get(2), &password);
        JSB_PRECONDITION2(ok, cx, false, "js_unzip_to_path : Error processing arguments");
        
        //JS::RootedObject callback(cx, args.get(3).toObjectOrNull());
        
        //int ret=ZipUtil::getInstance()->unzip(zipFileName,unzipPath,password,callback);
        int ret=ccsp::ZipUtil::getInstance()->unzip(zipFileName,unzipPath,password);
        jsval jsret = JSVAL_NULL;
        jsret = INT_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }
    
    JS_ReportError(cx, "js_unzip_to_path : wrong number of arguments");
    return false;
}

//jsb.unzipToPathAsync(zipFileName,pathName,"");
bool js_unzip_to_path_async(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    if (argc == 3)
    {
        std::string zipFileName;
        std::string unzipPath;
        std::string password;
        bool ok = jsval_to_std_string(cx, args.get(0), &zipFileName);
        JSB_PRECONDITION2(ok, cx, false, "js_unzip_to_path_async : Error processing arguments");
        
        ok = jsval_to_std_string(cx, args.get(1), &unzipPath);
        JSB_PRECONDITION2(ok, cx, false, "js_unzip_to_path_async : Error processing arguments");
        
        ok = jsval_to_std_string(cx, args.get(2), &password);
        JSB_PRECONDITION2(ok, cx, false, "js_unzip_to_path_async : Error processing arguments");
        
        int ret=ccsp::ZipUtil::getInstance()->unzipAsync(zipFileName,unzipPath,password);
        
        jsval jsret = JSVAL_NULL;
        jsret = INT_TO_JSVAL(ret);
        args.rval().set(jsret);
        
        return true;
    }
    
    JS_ReportError(cx, "js_unzip_to_path_async : wrong number of arguments");
    return false;
}

bool js_unzip_get_progress(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    
    int ret=ccsp::ZipUtil::getInstance()->getCurrentNum();
    jsval jsret = JSVAL_NULL;
    jsret = INT_TO_JSVAL(ret);
    args.rval().set(jsret);
    return  true;
}

bool js_unzip_get_total(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    
    int ret=ccsp::ZipUtil::getInstance()->getTotalNum();
    jsval jsret = JSVAL_NULL;
    jsret = INT_TO_JSVAL(ret);
    args.rval().set(jsret);
    return  true;
}

bool js_cocos2dx_Camera_unprojectGL(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cocos2d::Camera* cobj = (cocos2d::Camera *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_Camera_unprojectGL : Invalid Native Object");
    if (argc >= 2) {
        cocos2d::Size arg0;
        cocos2d::Vec3 arg1;
        cocos2d::Vec3 ret;
        ok &= jsval_to_ccsize(cx, args.get(0), &arg0);
        ok &= jsval_to_vector3(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_Camera_unprojectGL : Error processing arguments");
        cobj->unprojectGL(arg0, &arg1, &ret);
        args.rval().set(vector3_to_jsval(cx, ret));
        return true;
    }
    else if (argc == 1)
    {
        cocos2d::Vec3 arg0;
        ok &= jsval_to_vector3(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_Camera_unprojectGL : Error processing arguments");
        cocos2d::Vec3 ret = cobj->unprojectGL(arg0);
        args.rval().set(vector3_to_jsval(cx, ret));
        return true;
    }
    JS_ReportError(cx, "js_cocos2dx_Camera_unprojectGL : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}
	
bool js_texture_print_plist_info(JSContext *cx, uint32_t argc, jsval *vp)
{
    //JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    ccsp::TextureUtil::getInstance()->printPlistInfo();
    return  true;
}

bool js_texture_print_sprite_frames_info(JSContext *cx, uint32_t argc, jsval *vp)
{
    //JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    ccsp::TextureUtil::getInstance()->printSpriteFramesInfo();
    return  true;
}

bool js_DataUtil_getBuf(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    ccsp::DataUtil* cobj = (ccsp::DataUtil *)(proxy ? proxy->ptr : NULL);
//    JSB_PRECONDITION2( cobj, cx, false, "js_cocos2dx_DataUtil_getBuf : Invalid Native Object");
    if (argc == 1)
    {
        do{
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_DataUtil_getBuf : Error processing arguments");
            unsigned char* buf = ccsp::DataUtil::getInstance()->getBuf(arg0);
            int size = ccsp::DataUtil::getInstance()->getLength(arg0);
            if(!buf || !size){
                JS_ReportError(cx, "js_cocos2dx_DataUtil_getBuf : no data %s saved in DataUtil", arg0.c_str());
                break;
            }
            
            JS::RootedObject array(cx, JS_NewUint8Array(cx, size));
            if (nullptr == array)
                break;
            
            uint8_t* bufdata = (uint8_t*)JS_GetArrayBufferViewData(array);
            memcpy(bufdata, buf, size*sizeof(uint8_t));
            
            args.rval().set(OBJECT_TO_JSVAL(array));
            return true;
        }while(false);
    }
    JS_ReportError(cx, "js_cocos2dx_DataUtil_getBuf : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}

bool js_DataUtil_freeBuf(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    if (argc == 1)
    {
        do{
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            JSB_PRECONDITION2(ok, cx, false, "js_DataUtil_freeBuf : Error processing arguments");
            ccsp::DataUtil::getInstance()->freeBuf(arg0);
            return true;
        }while(false);
    }
    JS_ReportError(cx, "js_DataUtil_freeBuf : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}

bool js_UIUtil_seekNodeByName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        cocos2d::Node* arg0 = nullptr;
        std::string arg1;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_cocos2dx_ui_Helper_seekWidgetByName : Error processing arguments");
        
        cocos2d::Node* ret = ccsp::UIUtil::getInstance()->seekNodeByName(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::Node>(cx, (cocos2d::Node*)ret));
        } else {
            jsret = JSVAL_NULL;
        };
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_UIUtil_seekNodeByName : wrong number of arguments");
    return false;
}

bool js_EventUtil_getUserDataAsJsonString(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = false;
//    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    if (argc == 1)
    {
        cocos2d::EventCustom* arg0 = nullptr;
        do {
            if (args.get(0).isNull())
                break;
            if (!args.get(0).isObject())
                break;
            js_proxy_t *jsProxy;
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (cocos2d::EventCustom*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
            ok=true;
        } while (0);
        
        if (!ok){
            JS_ReportError(cx, "js_EventUtil_getUserDataAsJsonString : wrong number of arguments: %d, was expecting %d", argc, 1);
            return false;
        }
        std::string jsonString = ccsp::EventUtil::getInstance()->getUserDataAsJsonString(arg0);
        JS::RootedValue jsret(cx);
        jsret=std_string_to_jsval(cx,jsonString);
        args.rval().set(jsret);
        return true;
    }
   
    JS_ReportError(cx, "js_EventUtil_getUserDataAsJsonString : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}

void register_all_cocos2dx_ccsp(JSContext* cx, JS::HandleObject global)
{
    JS::RootedObject jsbObj(cx);
    JS::RootedObject logUtilObj(cx);
    JS::RootedObject httpUtilObj(cx);
    JS::RootedObject fileUtilObj(cx);
    JS::RootedObject zipUtilObj(cx);
 	JS::RootedObject dataUtilObj(cx);
    JS::RootedObject uiUtilObj(cx);
     JS::RootedObject textureUtilObj(cx);
     JS::RootedObject eventUtilObj(cx);
    
    JS::RootedObject tmpObj(cx);
   
   
    get_or_create_js_obj(cx, global, "jsb", &jsbObj);
    get_or_create_js_obj(cx, jsbObj, "fileUtil", &fileUtilObj);
    get_or_create_js_obj(cx, jsbObj, "logUtil", &logUtilObj);
    get_or_create_js_obj(cx, jsbObj, "httpUtil", &httpUtilObj);
    get_or_create_js_obj(cx, jsbObj, "zipUtil", &zipUtilObj);
    get_or_create_js_obj(cx, jsbObj, "textureUtil", &textureUtilObj);
    get_or_create_js_obj(cx, jsbObj, "dataUtil", &dataUtilObj);
    get_or_create_js_obj(cx, jsbObj, "uiUtil", &uiUtilObj);
    get_or_create_js_obj(cx, jsbObj, "eventUtil", &eventUtilObj);
    
    JS_DefineFunction(cx, fileUtilObj, "copyFile", js_copy_file, 2, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, logUtilObj, "enableLogToFile", js_enableLogToFile, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, logUtilObj, "setLogFileFullName", js_setLogFileFullName, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, httpUtilObj, "setConnectTimeOut", js_setConnectTimeOut, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, httpUtilObj, "setReadTimeOut", js_setReadTimeOut, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    
    JS_DefineFunction(cx,zipUtilObj, "unzipToPath", js_unzip_to_path, 3, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx,zipUtilObj, "unzipToPathAsync", js_unzip_to_path_async,3,JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx,zipUtilObj, "unzipGetProgress", js_unzip_get_progress, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx,zipUtilObj, "unzipGetTotal", js_unzip_get_total, 0, JSPROP_READONLY | JSPROP_PERMANENT);


    tmpObj.set(jsb_cocos2d_Camera_prototype);
    JS_DefineFunction(cx, tmpObj, "unprojectGL", js_cocos2dx_Camera_unprojectGL, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    
    JS_DefineFunction(cx,textureUtilObj, "printPlistInfo", js_texture_print_plist_info, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx,textureUtilObj, "printSpriteFramesInfo", js_texture_print_sprite_frames_info, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    
     JS_DefineFunction(cx, dataUtilObj, "getBuf", js_DataUtil_getBuf, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, dataUtilObj, "freeBuf", js_DataUtil_freeBuf, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    
    JS_DefineFunction(cx,uiUtilObj, "seekNodeByName", js_UIUtil_seekNodeByName, 2, JSPROP_READONLY | JSPROP_PERMANENT);

     JS_DefineFunction(cx,eventUtilObj, "getUserDataAsJsonString", js_EventUtil_getUserDataAsJsonString, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    
}
