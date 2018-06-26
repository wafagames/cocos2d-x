//
//  FlowField.hpp
//  cocos2d_libs
//
//  Created by joe on 2018/6/14.
//

#ifndef FlowField_h
#define FlowField_h

#include <stdio.h>

namespace ccsp {
    class FlowField{
    public:
        static void doParseByPFTable(int xNum,int yNum,int validTileCount,unsigned char* pfTable,
                                     std::function<void (unsigned char*,int)> cb);
        static void doParse(int xNum,int yNum,int validTileCount,unsigned char* pfTable,unsigned char* ffTable,
                            int startIndex,int count);
        static void clean();
    };
}

#endif /* FlowField_h */
