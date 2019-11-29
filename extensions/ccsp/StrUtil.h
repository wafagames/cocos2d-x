//
//  DataUtil.hpp
//  cocos2d_libs
//
//  Created by joe on 2017/7/19.
//
//

#ifndef StrUtil_h
#define StrUtil_h

#include <stdio.h>
#include <map>
#include <vector>

namespace ccsp{
    class StrUtil
    {
    public:
        static std::vector<std::string> explode(std::string s,char splitChar);
         static std::string trim(std::string s);
    };
}


#endif
