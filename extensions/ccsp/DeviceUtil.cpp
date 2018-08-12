//
//  DeviceUtil.cpp
//  cocos2d_libs
//
//  Created by joe on 2018/6/26.
//

#include "DeviceUtil.h"
#include "platform/CCPlatformConfig.h"
#include "cocos2d.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include <jni.h>
#include "cocos/platform/android/jni/JniHelper.h"
#elif CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#include <sys/sysctl.h>
#endif

using namespace ccsp;
using namespace cocos2d;

int DeviceUtil::getCpuCoreNum(){
    int coreNum=0;
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    size_t len=sizeof(coreNum);
    sysctlbyname("hw.ncpu",&coreNum,&len,NULL,0);
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    coreNum=JniHelper::callStaticIntMethod("org/android/util/DeviceUtil", "getNumberOfCPUCores");
#endif
     if(coreNum<=0){
        CCLOG("DeviceUtil.getCpuCoreNum:get coreNum is %d,set to 1",coreNum);
         coreNum=1;
     }
    return  coreNum;
}
