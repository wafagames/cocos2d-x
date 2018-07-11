//
//  HttpUtil.h
//  cocos2d_libs
//
//  Created by Joe on 2018/7/9.
//

#ifndef HttpUtil_h
#define HttpUtil_h

#include <stdio.h>

namespace ccsp {
    class HttpUtil {
        public :
        static bool post(const char* szUrl,const char* fileName,std::function<void(int code,const char* strResponse)>);
        static bool postBinary(const char* szUrl,const char* szParam,void* buf,int len);
        static bool get(const char* szUrl,std::function<void(int code,const char* strResponse)>);
    };
    
}
#endif /* HttpUtil_h */
