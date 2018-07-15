//
//  ZipUtil.cpp
//  cocos2d_libs
//
//  Created by Joe on 2017/03/28.
//
//

#include "ZipUtil.h"
//#include "FileUtil.h"
#include "platform/CCFileUtils.h"
#include "base/ccUTF8.h"

using namespace ccsp;
using namespace cocos2d;

static ZipUtil* s_instance=NULL;

ZipUtil* ZipUtil::getInstance(){
    if(!s_instance){
        s_instance=new ZipUtil();
    }
    return s_instance;
}


ZipUtil::ZipUtil(){
    
}

//int ZipUtil::unzip(std::string &zipFileName,std::string &unzipPath,std::string &password,JS::HandleObject callback)
int ZipUtil::unzip(std::string &zipFileName,std::string &unzipPath,std::string &password)
{
    _fileName=zipFileName;
    _unzipPath=unzipPath;
    _password=password;
    _totalNum=0;
    _currentNum=0;
    _async=false;
    _onProgress=NULL;
    
    return _unzip();
}

int ZipUtil::unzipAsyncWithCB(std::string zipFileName,std::string unzipPath,std::string password,std::function<void(int,int)> cb){
    _fileName=zipFileName;
    _unzipPath=unzipPath;
    _password=password;
    _totalNum=0;
    _currentNum=0;
    _async=true;
    _onProgress=cb;
     _cb_call_index=0;
    
    unz_global_info globalInfo = {0};
    std::string fullFileName=FileUtils::getInstance()->fullPathForFilename(_fileName);
    unzFile _unzFile = cocos2d::unzOpen(fullFileName.c_str());
    if (_unzFile){
        unzGetGlobalInfo(_unzFile, &globalInfo);
        unzCloseCurrentFile(_unzFile);
    }
    
    auto t = std::thread(&ZipUtil::_unzip, this);
    t.detach();
    
    _totalNum=(int)globalInfo.number_entry;
    return _totalNum;
}

int ZipUtil::unzipAsync(std::string &zipFileName,std::string &unzipPath,std::string &password){
    
   _fileName=zipFileName;
   _unzipPath=unzipPath;
   _password=password;
   _totalNum=0;
   _currentNum=0;
   _async=true;
    _onProgress=NULL;
   
   unz_global_info globalInfo = {0};
    std::string fullFileName=FileUtils::getInstance()->fullPathForFilename(_fileName);
   unzFile _unzFile = cocos2d::unzOpen(fullFileName.c_str());
   if (_unzFile){
       unzGetGlobalInfo(_unzFile, &globalInfo);
       unzCloseCurrentFile(_unzFile);
   }
   
   auto t = std::thread(&ZipUtil::_unzip, this);
   t.detach();
   
   _totalNum=(int)globalInfo.number_entry;
    return _totalNum;
}

int ZipUtil::_unzip(){
   bool success = true;
   unsigned char buffer[4096] = {0};
   char fileNameBuf[1024]={0};
   int ret=0;
   unz_global_info globalInfo = {0};
   
   std::string fullFileName=FileUtils::getInstance()->fullPathForFilename(_fileName);
   unzFile _unzFile = cocos2d::unzOpen(fullFileName.c_str());
   if (!_unzFile){
       CCLOG("ZipUtil::_unzip unzOpen %s failed",fullFileName.c_str());
       success=false;
       return 0;
   }
   
   if (unzGetGlobalInfo(_unzFile, &globalInfo) != UNZ_OK) {
       CCLOG("ZipUtil::_unzip unzGetGlobalInfo %s failed",fullFileName.c_str());
       success=false;
       return 0;
   }
   
   CCLOG("ZipUtil::_unzip zipfile %s have entry %lu, unzip to %s",_fileName.c_str(),globalInfo.number_entry,_unzipPath.c_str());
   _totalNum=(int)globalInfo.number_entry;
   
   unzGoToFirstFile(_unzFile);
   do {
       if (_password.size() == 0)
           ret = unzOpenCurrentFile(_unzFile);
       else
           ret = unzOpenCurrentFilePassword(_unzFile, _password.c_str());
       if (ret != UNZ_OK) {
           if(!_password.size())
               CCLOGERROR("ZipUtil::_unzip unzOpenCurrentFile failed");
           else
               CCLOGERROR("ZipUtil::_unzip unzOpenCurrentFilePassword failed");
           success = false;
           break;
       }
       // reading data and write to file
       int read ;
       unz_file_info fileInfo = {0};
       
       memset(fileNameBuf, 0, sizeof(fileNameBuf));
       unzGetCurrentFileInfo(_unzFile, &fileInfo, fileNameBuf, sizeof(fileNameBuf), nullptr, 0, nullptr, 0);
       
       std::string fullPath = _unzipPath + StringUtils::format("%s",fileNameBuf);
       
       int fileLen=(int)strlen(fileNameBuf);
       if (fileNameBuf[fileLen - 1] == '/' || fileNameBuf[fileLen - 1] == '\\')
           FileUtils::getInstance()->createDirectory(fullPath.c_str());
       else
       {
           FILE* fp = fopen(fullPath.c_str(), "wb");
           if(!fp){
               CCLOGERROR("ZipUtil::_unzip fopen %s failed %d %s",fullPath.c_str(),errno,strerror(errno));
               success=false;
               break;
           }
           while (true) {
               read = unzReadCurrentFile(_unzFile, buffer, 4096);
               if (read > 0) {
                   fwrite(buffer, read, 1, fp);
               }
               else
                   break;
           }
           fclose(fp);
       }
       unzCloseCurrentFile(_unzFile);
       ret = unzGoToNextFile(_unzFile);
       _currentNum++;
       if(_onProgress){
           Director::getInstance()->getScheduler()->performFunctionInCocosThread([&](){
               _onProgress(_cb_call_index,_totalNum);
               _cb_call_index++;
           });
       }
   } while (ret == UNZ_OK);
   return  _totalNum;
}
