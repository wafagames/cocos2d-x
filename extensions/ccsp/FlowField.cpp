//
//  FlowField.cpp
//  cocos2d_libs
//
//  Created by joe on 2018/6/14.
//

#include <cstdio>
#include <thread>
#include <mutex>
#include <chrono>
#include "FlowField.h"
#include "DeviceUtil.h"
#include  "cocos2d.h"

using namespace ccsp;
using namespace cocos2d;

static int s_jobNum=0;
static int s_jobDone=0;
static std::mutex s_mtx;
static std::condition_variable s_cv;
static unsigned char* s_ffTable;
static int s_bufSize=0;
static std::function<void (unsigned char*,int)> s_cb;
std::vector<std::thread> s_threadVector;
//static void waitJob(){
//    if(s_jobDone<s_jobNum){
//         CCLOG("FlowField.waitJob:%d finished, %d total,wait threads",s_jobDone,s_jobNum);
//        for(auto &thread:s_threadVector){
//            if(thread.joinable())
//                thread.join();
//        }
//    }else{
//        CCLOG("FlowField.waitJob:job finished, no need to wait");
//    }
//    //job finished
//    if(s_cb){
//        CCLOG("FlowField.waitJob:all threads finished,performFunctionInCocosThread");
//        Director::getInstance()->getScheduler()->performFunctionInCocosThread([&](){
//             s_cb(s_ffTable,s_bufSize);
//        });
//    }
//}

static void threadParseByPFTable(int xNum, int yNum, int validTileCount,unsigned char *pfTable,
                                 std::function<void (unsigned char*,int)> cb){
    int cores=DeviceUtil::getCpuCoreNum();
    int c2=std::thread::hardware_concurrency();
    CCLOG("FlowField.doParseByPFTable:cores from DeviceUtil %d, hardware_concurrency %d",cores,c2);
    int total=xNum*yNum;
    s_threadVector.clear();
    if(!s_ffTable){
        s_bufSize=total*validTileCount;
        s_ffTable=(unsigned char*)malloc(s_bufSize);
        CCLOG("FlowField.doParseByPFTable:malloc %.2fM",((float)s_bufSize)/1024/1024);
    }
    if(s_bufSize && s_bufSize!=total*validTileCount){
        free(s_ffTable);
        s_bufSize=total*validTileCount;
        s_ffTable=(unsigned char*)malloc(s_bufSize);
        CCLOG("FlowField.doParseByPFTable:free and re-alloc %.2fM",((float)s_bufSize)/1024/1024);
    }
    memset(s_ffTable,0,s_bufSize);
    
    s_cb=cb;
    int count=total/cores;
    int checked=0;
    int needCheck=count;
    s_jobNum=0;
    s_jobDone=0;

    while (checked<total) {
        s_jobNum++;
        std::thread jobThread(FlowField::doParse,xNum,yNum,validTileCount,pfTable,s_ffTable,checked,needCheck);
        s_threadVector.push_back(std::move(jobThread));
        checked+=needCheck;
        if(checked+count>total)
            needCheck=total-checked;
        if(!needCheck)
            break;
    }
    CCLOG("FlowField.doParseByPFTable:%d threads created",s_jobNum);
    for(auto &thread:s_threadVector){
        thread.join();
    }
//    std::thread waitThread(waitJob);
//    waitThread.detach();
    if(s_cb){
        CCLOG("FlowField.waitJob:all threads finished,performFunctionInCocosThread");
        Director::getInstance()->getScheduler()->performFunctionInCocosThread([&](){
            s_cb(s_ffTable,s_bufSize);
        });
    }
}

void FlowField::doParseByPFTable(int xNum, int yNum, int validTileCount,unsigned char *pfTable,
                                 std::function<void (unsigned char*,int)> cb){
    std::thread doJob(threadParseByPFTable,xNum,yNum,validTileCount,pfTable,cb);
    doJob.detach();
}

void FlowField::clean(){
    if(s_bufSize){
        free(s_ffTable);
        s_bufSize=0;
        s_ffTable=NULL;
    }
}

//static void printLog(int startIndex,int newIndex,int value,const char* d){
//    CCLOG("round %d,index %d write value %d(%s)",startIndex,newIndex,value,d);
//}

void FlowField::doParse(int xNum, int yNum, int validTileCount, unsigned char *pfTable, 
                   unsigned char *ffTable, int index, int count){
    //std::unique_lock<std::mutex> lock(s_mtx);
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
        if(startIndex==3){
            arraySize=1024;
        }
        xyArr1[0]=x;
        xyArr1[1]=y;
        ffTable[offset+startIndex]=1;
        filled=1;
        xyArrLength=2;
        if(offset+maxIndex>s_bufSize){
            CCLOG("FlowField.doParse:exceed buf limit,error!!!! bufsize %d,offset %d,maxIndex %d",s_bufSize,offset,maxIndex);
            break;
        }
       
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
                    //printLog(startIndex,newIndex,value+1,"left");
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
                    //printLog(startIndex,newIndex,value+1,"left_down");
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
                    //printLog(startIndex,newIndex,value+1,"down");
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
                    //printLog(startIndex,newIndex,value+1,"right_down");
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
                    //printLog(startIndex,newIndex,value+1,"right");
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
                    //printLog(startIndex,newIndex,value+1,"right_up");
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
                    //printLog(startIndex,newIndex,value+1,"up");
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
                    //printLog(startIndex,newIndex,value+1,"left_up");
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
        //CCLog("%d checked",parseIndex);
    }
    //s_cv.notify_one();
    s_jobDone++;
}
