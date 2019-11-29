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
#include <string>
#include <algorithm>


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


std::string StrUtil::trim(std::string s){
    auto start=s.begin();
    while (start!=s.end() && std::isspace(*start))
        start++;
    auto end=s.end();
    do{
        end--;
    }while (std::distance(start,end)>0 && std::isspace(*end));
    return  std::string(start,end+1);
}
