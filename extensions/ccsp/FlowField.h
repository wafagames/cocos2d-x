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
        static void doParseByPFTable(int xNum,int yNum,unsigned char* pfTable,int validTileCount);
        static void doParse(int xNum,int yNum,unsigned char* pfTable,int validTileCount,unsigned char* ffTable,
                            int startIndex,int count);
    }
}

#endif /* FlowField_h */
