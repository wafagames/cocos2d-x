//
//  jsb_cocos2dx_ccsp_manual.h
//  cocos2d_js_bindings
//
//  Created by Joe on 16/2/25.
//
//

#ifndef jsb_cocos2dx_ccsp_h
#define jsb_cocos2dx_ccsp_h


#include "jsapi.h"
#include "jsfriendapi.h"
#include "mozilla/Maybe.h"
#include "cocos/network/HttpClient.h"
#include "extensions/ccsp/LogUtil.h"
#include "extensions/ccsp/FileUtil.h"
#include "extensions/ccsp/ZipUtil.h"
#include "extensions/ccsp/TimeUtil.h"
#include "extensions/ccsp/TextureUtil.h"

void register_all_cocos2dx_ccsp(JSContext* cx, JS::HandleObject global);



#endif /* jsb_cocos2dx_ccsp_h */
