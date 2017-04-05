//
//  ZipUtil.hpp
//  cocos2d_libs
//
//  Created by Joe on 2017/03/28.
//
//

#ifndef ZipUtil_hpp
#define ZipUtil_hpp

#include <stdio.h>
#include <string>

#include "external/unzip/unzip.h"

//namespace ccsp{
//    class ZipUtil
//    {
//    public:
//        static ZipUtil* getInstance();
//        int unzip(JSContext *cx, JS::HandleObject obj,std::string &zipFileName,std::string &unzipPath,std::string &password,JS::HandleObject callback);
//        int unzipAsync(JSContext *cx, JS::HandleObject obj,std::string &zipFileName,std::string &unzipPath,std::string &password);
//        int getCurrentNum(){return _currentNum;};
//        int getTotalNum(){return _totalNum;};
//        
//    protected:
//        ZipUtil();
//        void onProgress();
//        int _unzip();
//        
//    private:
//        JSContext *_cx;
//        JS::Heap<JSObject*> _obj;
//        JS::Heap<JSObject*> _jsCallback;
//        
//        std::string _fileName;
//        std::string _unzipPath;
//        std::string _password;
//        int _totalNum;
//        int _currentNum;
//        bool _async;
//        
//    };
//}

namespace ccsp{
    class ZipUtil
    {
    public:
        static ZipUtil* getInstance();
        //int unzip(std::string &zipFileName,std::string &unzipPath,std::string &password,JS::HandleObject callback);
        int unzip(std::string &zipFileName,std::string &unzipPath,std::string &password);
        int unzipAsync(std::string &zipFileName,std::string &unzipPath,std::string &password);
        int getCurrentNum(){return _currentNum;};
        int getTotalNum(){return _totalNum;};
        
    protected:
        ZipUtil();
        //void onProgress();
        int _unzip();
        
    private:
        //JS::Heap<JSObject*> _jsCallback;
        
        std::string _fileName;
        std::string _unzipPath;
        std::string _password;
        int _totalNum;
        int _currentNum;
        bool _async;
        
    };
}

#endif /* ZipUtil_hpp */
