//
//  jsb_cocos2dx_ccsp_manual.cpp
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

void register_all_cocos2dx_ccsp(JSContext* cx, JS::HandleObject global)
{
    JS::RootedObject jsbObj(cx);
    JS::RootedObject logUtilObj(cx);
    JS::RootedObject httpUtilObj(cx);
    JS::RootedObject fileUtilObj(cx);
    JS::RootedObject zipUtilObj(cx);
    JS::RootedObject textureUtilObj(cx);
   
    get_or_create_js_obj(cx, global, "jsb", &jsbObj);
    get_or_create_js_obj(cx, jsbObj, "fileUtil", &fileUtilObj);
    get_or_create_js_obj(cx, jsbObj, "logUtil", &logUtilObj);
    get_or_create_js_obj(cx, jsbObj, "httpUtil", &httpUtilObj);
    get_or_create_js_obj(cx, jsbObj, "zipUtil", &zipUtilObj);
    get_or_create_js_obj(cx, jsbObj, "textureUtil", &textureUtilObj);
    
    JS_DefineFunction(cx, fileUtilObj, "copyFile", js_copy_file, 2, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, logUtilObj, "enableLogToFile", js_enableLogToFile, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, logUtilObj, "setLogFileFullName", js_setLogFileFullName, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, httpUtilObj, "setConnectTimeOut", js_setConnectTimeOut, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, httpUtilObj, "setReadTimeOut", js_setReadTimeOut, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    
    JS_DefineFunction(cx,zipUtilObj, "unzipToPath", js_unzip_to_path, 3, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx,zipUtilObj, "unzipToPathAsync", js_unzip_to_path_async,3,JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx,zipUtilObj, "unzipGetProgress", js_unzip_get_progress, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx,zipUtilObj, "unzipGetTotal", js_unzip_get_total, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    
    JS_DefineFunction(cx,textureUtilObj, "printPlistInfo", js_texture_print_plist_info, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx,textureUtilObj, "printSpriteFramesInfo", js_texture_print_sprite_frames_info, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    
}
