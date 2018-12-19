//
//  PkgUtiliOS.cpp
//  cocos2d_libs
//
//  Created by joe on 2018/12/18.
//

#include "platform/CCPlatformConfig.h"
#include "platform/CCCommon.h"

#include <stdarg.h>
#include <stdio.h>

#include "PkgUtil.h"

namespace ccsp {
    std::string PkgUtil::getPkgName()
    {
        NSString *app_Name = [[NSBundle mainBundle]bundleIdentifier];
        std::string *name = new std::string([app_Name UTF8String]);
        return *name;
    }
}
