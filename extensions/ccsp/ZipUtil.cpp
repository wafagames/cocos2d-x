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
    
    return _unzip();
}
                   
int ZipUtil::unzipAsync(std::string &zipFileName,std::string &unzipPath,std::string &password){
    
   _fileName=zipFileName;
   _unzipPath=unzipPath;
   _password=password;
   _totalNum=0;
   _currentNum=0;
   _async=true;
   
   unz_global_info globalInfo = {0};
    std::string fullFileName=FileUtils::getInstance()->fullPathForFilename(_fileName);
   unzFile _unzFile = cocos2d::unzOpen(fullFileName.c_str());
   if (_unzFile){
       unzGetGlobalInfo(_unzFile, &globalInfo);
       unzCloseCurrentFile(_unzFile);
   }
   
   auto t = std::thread(&ZipUtil::_unzip, this);
   t.detach();
   
   _totalNum=globalInfo.number_entry;
   return globalInfo.number_entry;
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
       CCLOG("ZipMgr::_unzip unzOpen %s failed",fullFileName.c_str());
       success=false;
       return 0;
   }
   
   if (unzGetGlobalInfo(_unzFile, &globalInfo) != UNZ_OK) {
       CCLOG("ZipMgr::_unzip unzGetGlobalInfo %s failed",fullFileName.c_str());
       success=false;
       return 0;
   }
   
   CCLOG("ZipMgr::_unzip zipfile %s have entry %lu, unzip to %s",_fileName.c_str(),globalInfo.number_entry,_unzipPath.c_str());
   _totalNum=globalInfo.number_entry;
   
   unzGoToFirstFile(_unzFile);
   do {
       if (_password.size() == 0)
           ret = unzOpenCurrentFile(_unzFile);
       else
           ret = unzOpenCurrentFilePassword(_unzFile, _password.c_str());
       if (ret != UNZ_OK) {
           if(!_password.size())
               CCLOG("ZipMgr::_unzip unzOpenCurrentFile failed");
           else
               CCLOG("ZipMgr::_unzip unzOpenCurrentFilePassword failed");
           success = false;
           break;
       }
       // reading data and write to file
       int read ;
       unz_file_info fileInfo = {0};
       
       memset(fileNameBuf, 0, sizeof(fileNameBuf));
       unzGetCurrentFileInfo(_unzFile, &fileInfo, fileNameBuf, sizeof(fileNameBuf), nullptr, 0, nullptr, 0);
       
       std::string fullPath = _unzipPath + StringUtils::format("%s",fileNameBuf);
       
       int fileLen=strlen(fileNameBuf);
       if (fileNameBuf[fileLen - 1] == '/' || fileNameBuf[fileLen - 1] == '\\')
           FileUtils::getInstance()->createDirectory(fullPath.c_str());
       else
       {
           FILE* fp = fopen(fullPath.c_str(), "wb");
           if(!fp){
               CCLOG("ZipMgr::_unzip fopen %s failed",fullPath.c_str());
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
//       if(!_async){
//           onProgress();
//       }
   } while (ret == UNZ_OK);
   return  _totalNum;
}

//void ZipUtil::onProgress(){
//   jsval valArr[2];
//   valArr[0]=INT_TO_JSVAL(_currentNum);
//   valArr[1]=INT_TO_JSVAL(_totalNum);
//   
//   JS::RootedObject global(_cx, ScriptingCore::getInstance()->getGlobalObject());
//   JSAutoCompartment ac(_cx, global);
//   
//   JS::RootedValue callback(_cx, OBJECT_TO_JSVAL(_jsCallback));
//   if (!callback.isNull())
//   {
//       JS::RootedValue retval(_cx);
//       JS_CallFunctionValue(_cx, global, callback, JS::HandleValueArray::fromMarkedLocation(2, valArr), &retval);
//   }
//}
