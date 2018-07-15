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
namespace ccsp{
    class ZipUtil
    {
    public:
        static ZipUtil* getInstance();
        //int unzip(std::string &zipFileName,std::string &unzipPath,std::string &password,JS::HandleObject callback);
        int unzip(std::string &zipFileName,std::string &unzipPath,std::string &password);
        int unzipAsync(std::string &zipFileName,std::string &unzipPath,std::string &password);
        int unzipAsyncWithCB(std::string zipFileName,std::string unzipPath,std::string password,std::function<void(int,int)> cb);
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
        int _cb_call_index;
        bool _async;
        std::function <void(int,int)> _onProgress;
    };
}

#endif /* ZipUtil_hpp */
