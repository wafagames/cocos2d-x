//
//  Browser.cpp
//  cocos2d_libs
//
//  Created by joe on 2018/6/14.
//
#include <string>
#include "Browser.h"
#include  "cocos2d.h"

using namespace ccsp;
using namespace cocos2d;

void Browser::openUrl(std::string url){
    Application::getInstance()->openURL(url);
}

