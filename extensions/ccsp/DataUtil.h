//
//  DataUtil.hpp
//  cocos2d_libs
//
//  Created by joe on 2017/7/19.
//
//

#ifndef DataUtil_hpp
#define DataUtil_hpp

#include <stdio.h>
#include <map>

namespace ccsp{
    class DataUtil
    {
    public:
        static DataUtil* getInstance();
        DataUtil();
        int store(const std::string &key,unsigned char* buf,int length);
        unsigned char* getBuf(const std::string &key);
        int getLength(const std::string &key);
        void freeBuf(const std::string &key);
    private:
        std::map<std::string,unsigned char*> _map_data;
        std::map<std::string,int> _map_len;
    };
}


#endif /* DataUtil_hpp */
