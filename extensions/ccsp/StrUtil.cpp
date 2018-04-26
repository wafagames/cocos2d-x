//
//  DataUtil.cpp
//  cocos2d_libs
//
//  Created by joe on 2017/7/19.
//
//

#include "StrUtil.h"

#include <sstream>
#include <iostream>
#include <vector>

using namespace ccsp;

std::vector<std::string> StrUtil::explode(std::string str,char splitChar){
    std::vector<std::string> strings;
    std::istringstream f(str);
    std::string s;
    while (std::getline(f, s, splitChar)) {
        //cout << s << endl;
        strings.push_back(s);
    }
    return strings;
}
