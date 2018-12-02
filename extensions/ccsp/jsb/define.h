//
//  FileUtil.hpp
//  cocos2d_libs
//
//  Created by Joe on 2016/11/12.
//
//

#ifndef ccsp_jsb_define_h
#define ccsp_jsb_define_h

#define jsb_by_spiderMonkey

#include "cocos2d.h"


//#include "jsapi.h"
//#include "jsfriendapi.h"
//#include "mozilla/Maybe.h"



#ifdef jsb_by_spiderMonkey
    #include "cocos/scripting/js-bindings/manual/ScriptingCore.h"
    #include "SpiderMonkey/Util.h"
#endif

#endif
