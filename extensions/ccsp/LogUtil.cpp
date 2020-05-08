//
//  LogUtil.cpp
//  cocos2d_libs
//
//  Created by Joe on 2016/11/12.
//
//

#include <stdlib.h>
#include <cstring>
#include "LogUtil.h"
#include "TimeUtil.h"
#include "FileUtil.h"

#include "platform/CCFileUtils.h"

#define  CCSP_MAX_LOG_LENGTH 16*1024

using namespace ccsp;
using namespace cocos2d;

static LogUtil* s_instance=NULL;

LogUtil* LogUtil::getInstance(){
    if(!s_instance){
        s_instance=new LogUtil();
    }
    return s_instance;
}

LogUtil::LogUtil(){
    _rootPath=cocos2d::FileUtils::getInstance()->getWritablePath();
}

void LogUtil::logToFileWithTime(const char *szFmt, ...){
    va_list args;
    va_start(args, szFmt);
    //char szTimeBuf[128]={0};
    char* szLog;
    if(!_bEnable  || _strLogFileName.length()<=0)
        return;
    szLog=(char*)malloc(CCSP_MAX_LOG_LENGTH);
    memset(szLog,0,CCSP_MAX_LOG_LENGTH);
    
    TimeUtil::getInstance()->getTimeStrLong(szLog, CCSP_MAX_LOG_LENGTH);
    unsigned long len=strlen(szLog);
    szLog[len++]=0x20;
    vsnprintf(&szLog[len], CCSP_MAX_LOG_LENGTH-len, szFmt, args);
    FileUtil::getInstance()->appendString(_strLogFileName,std::string(szLog));
    free(szLog);
    va_end(args);
    return;
}

void LogUtil::logByFileName(const char *fileName, const char *szFmt, ...){
    va_list args;
    va_start(args, szFmt);
    char* szLog;
    if(!_bEnable  || !fileName)
        return;
    szLog=(char*)malloc(CCSP_MAX_LOG_LENGTH);
    memset(szLog,0,CCSP_MAX_LOG_LENGTH);
    
    TimeUtil::getInstance()->getTimeStrLong(szLog, CCSP_MAX_LOG_LENGTH);
    unsigned long len=strlen(szLog);
    szLog[len++]=0x20;
    vsnprintf(&szLog[len], CCSP_MAX_LOG_LENGTH-len, szFmt, args);
    FileUtil::getInstance()->appendString(_rootPath+fileName,std::string(szLog));
    free(szLog);
    va_end(args);
    return;
}

void LogUtil::logBy2FileName(const char *fileName1,const char *fileName2, const char *szFmt, ...){
    va_list args;
    va_start(args, szFmt);
    char* szLog;
    if(!_bEnable  || !fileName1 | !fileName2)
        return;
    szLog=(char*)malloc(CCSP_MAX_LOG_LENGTH);
    memset(szLog,0,CCSP_MAX_LOG_LENGTH);
    
    TimeUtil::getInstance()->getTimeStrLong(szLog, CCSP_MAX_LOG_LENGTH);
    unsigned long len=strlen(szLog);
    szLog[len++]=0x20;
    vsnprintf(&szLog[len], CCSP_MAX_LOG_LENGTH-len, szFmt, args);
    FileUtil::getInstance()->appendString(_rootPath+fileName1,std::string(szLog));
    FileUtil::getInstance()->appendString(_rootPath+fileName2,std::string(szLog));
    free(szLog);
    va_end(args);
    return;
}


void LogUtil::clear(){
    if(_strLogFileName.empty())
        return;
    FileUtil::getInstance()->deleteFile(_strLogFileName);
    return;
}
