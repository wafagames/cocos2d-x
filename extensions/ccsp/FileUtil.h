//
//  FileUtil.hpp
//  cocos2d_libs
//
//  Created by Joe on 2016/11/12.
//
//

#ifndef FileUtil_hpp
#define FileUtil_hpp

#include <stdio.h>
#include <string>

namespace ccsp{
    class FileUtil
    {
    public:
        static FileUtil* getInstance();
        bool copyFile(std::string &srcFullPath,std::string &dstFullPath);
        bool appendString(const std::string &fullPathName,const std::string &str);
        void deleteFile(const std::string &fullPathName);
    };
}

#endif /* FileUtil_hpp */
