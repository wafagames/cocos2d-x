//
//  DirUtil.cpp
//  cocos2d_libs
//
//  Created by joe on 2018/12/18.
//

#include "DirUtil.h"

#include "platform/CCFileUtils.h"

using namespace ccsp;
using namespace cocos2d;

bool DirUtil::isExists(const std::string &srcPath)
{
    return cocos2d::FileUtils::getInstance()->isDirectoryExist(srcPath);
}

bool DirUtil::mkdir(const std::string &srcPath)
{
    return cocos2d::FileUtils::getInstance()->createDirectory(srcPath);
}

bool DirUtil::rmdir(const std::string &srcPath){
    return cocos2d::FileUtils::getInstance()->removeDirectory(srcPath);
}
