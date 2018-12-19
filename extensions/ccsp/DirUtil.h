//
//  DirUtil.h
//  cocos2d_libs
//
//  Created by joe on 2018/12/18.
//

#ifndef DirUtil_h
#define DirUtil_h

#include <stdio.h>
#include <string>

namespace ccsp{
    class DirUtil
    {
    public:
        static bool isExists(const std::string &srcPath);
        static bool mkdir(const std::string &srcPath);
        static bool rmdir(const std::string &srcPath);
    };
}

#endif /* DirUtil_h */
