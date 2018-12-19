//
//  VersionUtil.hpp
//  cocos2d_libs
//
//  Created by joe on 2018/12/17.
//
//

#ifndef VersionUtil_h
#define VersionUtil_h

#include <stdio.h>
#include <map>
#include <vector>

namespace ccsp{
    class VersionUtil
    {
    public:
        static int compare(std::string strV1,std::string strV2);
    };
}


#endif
