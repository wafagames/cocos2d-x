//
//  FlowField.cpp
//  cocos2d_libs
//
//  Created by joe on 2018/6/14.
//

#include "FlowField.h"

using namespace ccsp;

void FlowField::doParseByPFTable(int xNum, int yNum, unsigned char *pfTable, int validTileCount){
    
}

void FlowField::doParse(int xNum, int yNum, unsigned char *pfTable, int validTileCount,
                   unsigned char *ffTable, int index, int count){
    int x=0;
    int y=0;
    int parseIndex=0;
    int startIndex=0;
    int filled=0;
    int maxIndex=xNum*yNum;
    unsigned char xyArr1[1024]={0};
    unsigned char xyArr2[1024]={0};
    int xyArrLength=0;
    
    int indexCheck1=0;
    int indexCheck2=0;
    int value=0;
    int newX=0;
    int newY=0;
    int newIndex=0;
    
    //calc init offset in ff table
    int offset=0;
    int k=0;
    for(int i=0;i<index;i++){
        if(pfTable[i]==0)
            k++;
    }
    offset=k*xNum*yNum;
    
    for(int j=0;j<count;j++){
        parseIndex=index+j;
        if(pfTable[parseIndex])
            continue;

        x=parseIndex%xNum;
        y=parseIndex/xNum;
        startIndex=x+xNum*y;
        xyArr1[0]=x;
        xyArr2[1]=y;
        ffTable[offset+startIndex]=1;
        filled=1;
        xyArrLength=2;
        while(true){
            for(int i=0;i<xyArrLength;i+=2){
                x=xyArr1[i];
                y=xyArr1[i+1];
                value=ffTable[x+xNum*y];
                
                //left
                newX=x-1;
                newY=y;
                newIndex=newX+xNum*newY;
                if(newIndex>=0 && newIndex<maxIndex &&newX>=0 && newX<xNum
                   && newY>=0 && newY<yNum && newIndex!=startIndex
                   && pfTable[newIndex]==0 && ffTable[newIndex]){
                    
                }
            }
        }
        
        offset+=xNum*yNum;
    }
}
