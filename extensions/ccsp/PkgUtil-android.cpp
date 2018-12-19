//
//  PkgUtil.cpp
//  cocos2d_libs
//
//  Created by joe on 2018/12/18.
//

#include "PkgUtil.h"

#include "platform/CCPlatformConfig.h"
#include "cocos2d.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include <jni.h>
#include "cocos/platform/android/jni/JniHelper.h"
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#endif

using namespace ccsp;
using namespace cocos2d;

std::string PkgUtil::getPkgName(){
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    return JniHelper::callStaticStringMethod("org/android/util/PkgUtil", "getPkgName");
#endif
}
