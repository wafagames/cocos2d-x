//
//  FlowField.cpp
//  cocos2d_libs
//
//  Created by joe on 2018/6/14.
//

#include "FlowField.h"
#include "DeviceUtil.h"
#include <cstdio>
#include <thread>
#include <mutex>
#include <chrono>

using namespace ccsp;
static int s_jobNum=0;
static std::mutex s_mtx;
static std::condition_variable s_cv;
static unsigned char* s_ffTable;
static int s_bufSize=0;
static std::function<void (unsigned char*,int)> s_cb;

static void waitJob(){
    std::unique_lock<std::mutex> lock(s_mtx);
    int jobDone=0;
    while(jobDone < s_jobNum){
        s_cv.wait(lock);
        jobDone++;
    }
    
    //job finished
    if(s_cb){
        s_cb(s_ffTable,s_bufSize);
    }
}

void FlowField::doParseByPFTable(int xNum, int yNum, int validTileCount,unsigned char *pfTable,
                                 std::function<void (unsigned char*,int)> cb){
    int cores=DeviceUtil::getCpuCoreNum();
    int total=xNum*yNum;
    if(s_bufSize && s_bufSize!=total){
        free(s_ffTable);
        s_bufSize=total;
        s_ffTable=(unsigned char*)malloc(total);
    }
    memset(s_ffTable,0,total);
    
    s_cb=cb;
    int count=total/cores;
    int checked=0;
    int needCheck=count;
    s_jobNum=0;
    while (checked<total) {
        s_jobNum++;
        std::thread jobThread(FlowField::doParse,xNum,yNum,validTileCount,pfTable,s_ffTable,checked,needCheck);
        checked+=needCheck;
        if(checked+count>total)
            needCheck=total-checked;
    }
    std::thread waitThread(waitJob);
}


void FlowField::clean(){
    if(s_bufSize){
        free(s_ffTable);
        s_bufSize=0;
        s_ffTable=NULL;
    }
}

void FlowField::doParse(int xNum, int yNum, int validTileCount, unsigned char *pfTable, 
                   unsigned char *ffTable, int index, int count){
    std::unique_lock<std::mutex> lock(s_mtx);
    int x=0;
    int y=0;
    int parseIndex=0;
    int startIndex=0;
    int filled=0;
    int maxIndex=xNum*yNum;
    int arraySize=1024;
    unsigned char xyArr1[1024]={0};
    unsigned char xyArr2[1024]={0};
    int xyArrLength=0;
    
    int indexCheck1=0;
    int indexCheck2=0;
    int value=0;
    int newX=0;
    int newY=0;
    int newIndex=0;
    int k=0;
    //calc init offset in ff table
    int offset=0;
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
            k=0;
            for(int i=0;i<xyArrLength;i+=2){
                x=xyArr1[i];
                y=xyArr1[i+1];
                value=ffTable[offset+x+xNum*y];
                //left
                newX=x-1;
                newY=y;
                newIndex=newX+xNum*newY;
                if(newIndex>=0 && newIndex<maxIndex &&newX>=0 && newX<xNum
                   && newY>=0 && newY<yNum && newIndex!=startIndex
                   && pfTable[newIndex]==0 && ffTable[offset+newIndex]==0){
                    ffTable[offset+newIndex]=value+1;
                    filled++;
                    xyArr2[k]=newX;
                    xyArr2[k+1]=newY;
                    k+=2;
                }
                
                //left down
                newX=x-1;
                newY=y-1;
                newIndex=newX+xNum*newY;
                indexCheck1=x-1+xNum*y;
                indexCheck2=x+xNum*(y-1);
                if(newIndex>=0 && newIndex<maxIndex && newX>=0 && newX<xNum && newY>=0 && newY<yNum && newIndex!=startIndex && pfTable[newIndex]==0 && ffTable[offset+newIndex]==0
                   && (indexCheck1>=0 && indexCheck1<maxIndex ? pfTable[indexCheck1]==0 : true)
                   && (indexCheck2>=0 && indexCheck2<maxIndex ? pfTable[indexCheck2]==0 : true)){
                    ffTable[offset+newIndex]=value+1;
                    filled++;
                    xyArr2[k]=newX;
                    xyArr2[k+1]=newY;
                    k+=2;
                }
                
                //down
                newX=x;
                newY=y-1;
                newIndex=newX+xNum*newY;
                if(newIndex>=0 && newIndex<maxIndex && newX>=0 && newX<xNum && newY>=0 && newY<yNum && newIndex!=startIndex && pfTable[newIndex]==0 && ffTable[offset+newIndex]==0 ){
                    ffTable[offset+newIndex]=value+1;
                    filled++;
                    xyArr2[k]=newX;
                    xyArr2[k+1]=newY;
                    k+=2;
                }
                
                //right-down
                newX=x+1;
                newY=y-1;
                newIndex=newX+xNum*newY;
                indexCheck1=x+1+xNum*y;
                indexCheck2=x+xNum*(y-1);
                if(newIndex>=0 && newIndex<maxIndex && newX>=0 && newX<xNum && newY>=0 && newY<yNum && newIndex!=startIndex && pfTable[newIndex]==0 && ffTable[offset+newIndex]==0
                   && (indexCheck1>=0 && indexCheck1<maxIndex ? pfTable[indexCheck1]==0 : true)
                   && (indexCheck2>=0 && indexCheck2<maxIndex ? pfTable[indexCheck2]==0 : true)){
                    ffTable[offset+newIndex]=value+1;
                    filled++;
                    xyArr2[k]=newX;
                    xyArr2[k+1]=newY;
                    k+=2;
                }
                
                //right
                newX=x+1;
                newY=y;
                newIndex=newX+xNum*newY;
                if(newIndex>=0 && newIndex<maxIndex && newX>=0 && newX<xNum && newY>=0 && newY<yNum && newIndex!=startIndex && pfTable[newIndex]==0 && ffTable[offset+newIndex]==0 ){
                    ffTable[offset+newIndex]=value+1;
                    filled++;
                    xyArr2[k]=newX;
                    xyArr2[k+1]=newY;
                    k+=2;
                }
                
                //right-up
                newX=x+1;
                newY=y+1;
                newIndex=newX+xNum*newY;
                indexCheck1=x+1+xNum*y;
                indexCheck2=x+xNum*(y+1);
                if(newIndex>=0 && newIndex<maxIndex && newX>=0 && newX<xNum && newY>=0 && newY<yNum && newIndex!=startIndex && pfTable[newIndex]==0 && ffTable[offset+newIndex]==0
                   && (indexCheck1>=0 && indexCheck1<maxIndex ? pfTable[indexCheck1]==0 : true)
                   && (indexCheck2>=0 && indexCheck2<maxIndex ? pfTable[indexCheck2]==0 : true)){
                    ffTable[offset+newIndex]=value+1;
                    filled++;
                    xyArr2[k]=newX;
                    xyArr2[k+1]=newY;
                    k+=2;
                }
                
                //up
                newX=x;
                newY=y+1;
                newIndex=newX+xNum*newY;
                if(newIndex>=0 && newIndex<maxIndex && newX>=0 && newX<xNum && newY>=0 && newY<yNum && newIndex!=startIndex && pfTable[newIndex]==0 && ffTable[offset+newIndex]==0 ){
                    ffTable[offset+newIndex]=value+1;
                    filled++;
                    xyArr2[k]=newX;
                    xyArr2[k+1]=newY;
                    k+=2;
                }
                
                //left-up
                newX=x-1;
                newY=y+1;
                newIndex=newX+xNum*newY;
                indexCheck1=x-1+xNum*y;
                indexCheck2=x+xNum*(y+1);
                if(newIndex>=0 && newIndex<maxIndex && newX>=0 && newX<xNum && newY>=0 && newY<yNum && newIndex!=startIndex && pfTable[newIndex]==0 && ffTable[offset+newIndex]==0
                   && (indexCheck1>=0 && indexCheck1<maxIndex ? pfTable[indexCheck1]==0 : true)
                   && (indexCheck2>=0 && indexCheck2<maxIndex ? pfTable[indexCheck2]==0 : true)){
                    ffTable[offset+newIndex]=value+1;
                    filled++;
                    xyArr2[k]=newX;
                    xyArr2[k+1]=newY;
                    k+=2;
                }
            }
            xyArrLength=k;
            if(filled>=validTileCount || !xyArrLength)
                break;
            if(xyArrLength>=arraySize){
                //cannot support so big table,quit!
                break;
            }
            memset(xyArr1,0,arraySize);
            memcpy(xyArr1,xyArr2,arraySize);
        }
        offset+=maxIndex;
    }
    s_cv.notify_one();
}
