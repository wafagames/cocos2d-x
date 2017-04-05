//
//  FileUtil.cpp
//  cocos2d_libs
//
//  Created by Joe on 2016/11/12.
//
//

#include "FileUtil.h"
#include "platform/CCFileUtils.h"

using namespace ccsp;
using namespace cocos2d;
static FileUtil* s_instance=NULL;

FileUtil* FileUtil::getInstance(){
    if(!s_instance){
        s_instance=new FileUtil();
    }
    return s_instance;
}

bool FileUtil::copyFile(std::string &srcFullPath,std::string &dstFullPath)
{
    unsigned char* buf=0;
    unsigned int fileSize=0;
    auto fileData=cocos2d::FileUtils::getInstance()->getDataFromFile(srcFullPath);
    fileSize=(unsigned int)fileData.getSize();
    buf=(unsigned char*)malloc(fileSize);
    memcpy(buf,fileData.getBytes(),fileSize);
    
    auto hFile=fopen(dstFullPath.c_str(), "w+");
    if(!hFile){
        CCLOG("ccsp::FileUtil::copyFile fopen dstfile %s failed",dstFullPath.c_str());
        return false;
    }
    
    int writeSize=0;
    int onceWrite=1024*1000;
    if(fileSize<=onceWrite)
        fwrite(buf,1,fileSize,hFile);
    else{
        auto wsize=onceWrite;
        while (writeSize<fileSize) {
            wsize= wsize>fileSize-writeSize ? fileSize-writeSize : onceWrite;
            auto size=fwrite(&buf[writeSize],1,wsize,hFile);
            writeSize+=size;
            CCLOG("ccsp::FileUtil::copyFile write size %d total %d %d",(unsigned int)size,writeSize,fileSize);
        }
    }
    fclose(hFile);
    free(buf);
    CCLOG("ccsp::FileUtil::copyFile copy file to %s ok",dstFullPath.c_str());
    return  true;
}

bool FileUtil::appendString(const std::string &fullPathName,const std::string &str){
    Data fileData;
    fileData.copy((unsigned char*)str.c_str(), str.size());
    
    size_t size = 0;
    const char* mode = "ab+";
    
    CCASSERT(!fullPathName.empty() && fileData.getSize() != 0, "Invalid parameters.");
    
    auto fileutils = FileUtils::getInstance();
    do
    {
        // Read the file from hardware
        FILE *fp = fopen(fileutils->getSuitableFOpen(fullPathName).c_str(), mode);
        CC_BREAK_IF(!fp);
        size = fileData.getSize();
        
        fwrite(fileData.getBytes(), size, 1, fp);
        
        fclose(fp);
        
        return true;
    } while (0);
    
    return false;
}
