//
//  LogUtil.hpp
//  cocos2d_libs
//
//  Created by Joe on 2016/11/12.
//
//

#ifndef LogUtil_hpp
#define LogUtil_hpp

#include <stdio.h>
#include <string>

namespace ccsp {
class LogUtil {
    public :
        
    LogUtil();
    static LogUtil* getInstance();
    void enableLogToFile(bool bEnable){_bEnable=bEnable;};
    void enableCrashUpload(bool bEnable){_bEnableCrashUpload=bEnable;};
    bool isEnable(){return _bEnable;};
    bool isCrashUploadEnable(){return _bEnableCrashUpload;};
    void setLogFileFullName(const char* name){
        _strLogFileName=name;
    };
    //std::string getLogFileName(){return _strLogFileName;};
    void logToFileWithTime(const char* szFmt,...);
    void logByFileName(const char* fileName,const char* szFmt,...);
    void logBy2FileName(const char* fileName1,const char* fileName2,const char* szFmt,...);
    void uploadToUrl(const char *url,const char* szVersion,const char* szChannel, const char* fileName,int line,const char* msg);
    void clear();

    private:
        bool _bEnable;
        bool _bEnableCrashUpload;
        std::string _strLogFileName;
        std::string _rootPath;
};
    
}



#endif /* LogUtil_hpp */
