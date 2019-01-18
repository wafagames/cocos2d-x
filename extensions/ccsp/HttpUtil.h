//
//  HttpUtil.h
//  cocos2d_libs
//
//  Created by Joe on 2018/7/9.
//

#ifndef HttpUtil_h
#define HttpUtil_h

#include <stdio.h>
#include <functional>

namespace ccsp {
    class HttpUtil {
        public :
        static bool get(const char* szUrl,const char* szParam,std::function<void(int code,const char* strResponse)>);
        static bool post(const char* szUrl,const char* szParam,std::function<void(int code,const char* strResponse)>);
        static bool upload(const char* szUrl,const char* fileName,std::function<void(int code,const char* strResponse)>);
    };
    
}
#endif /* HttpUtil_h */
