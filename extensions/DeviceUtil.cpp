//
//  DeviceUtil.cpp
//  cocos2d_libs
//
//  Created by joe on 2018/6/26.
//

#include "DeviceUtil.h"
#include <sys/sysctl.h>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//#include <jni.h>
//#include "platform/android/jni/JniHelper.h"
#endif

using namespace ccsp;

int DeviceUtil::getCpuCoreNum(){
int coreNum=0;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    size_t len=sizeof(coreNum);
    sysctlbyname("hw.ncpu",&coreNum,&len,NULL,0);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//    JniMethodInfo t;
//    if (JniHelper::getStaticMethodInfo(t,"org/cocos2dx/javascript/Test","doMeAFavour","()I")){
//        int v=t.env->CallStaticIntMethod(t.classID, t.methodID);
//        t.env->DeleteLocalRef(t.classID);
//        return  v;
//    }
    coreNum=JniHelper::callStaticIntMethod("org/android/util/DeviceUtil", "getNumberOfCPUCores");
#endif
     if(coreNum<=0)
         coreNum=1;
    return  coreNum;
}
