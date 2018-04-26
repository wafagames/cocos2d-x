//
//  DataUtil.hpp
//  cocos2d_libs
//
//  Created by joe on 2017/7/19.
//
//

#ifndef StrUtil_hpp
#define StrUtil_hpp

#include <stdio.h>
#include <map>

namespace ccsp{
    class StrUtil
    {
    public:
        static std::vector<std::string> explode(std::string s,char splitChar);
    };
}


#endif
