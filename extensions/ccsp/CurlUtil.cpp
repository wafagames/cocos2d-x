//
//  CurlUtil.cpp
//  libcocos2d Mac
//
//  Created by Joe on 2018/7/12.
//

#include "CurlUtil.h"
#include <unistd.h>
#include <string.h>

using namespace ccsp;
USING_NS_CC;

std::function<void(long curSize,long totalSize,float speed)> s_cb_progress;
std::function<void(const char* strErr)> s_cb_error;
std::function<void(void)> s_cb_finished;
bool s_download_finished=false;

static size_t write_func(void *ptr, size_t size, size_t nmemb, void *userdata) {
    FILE *fp = (FILE*)userdata;
    size_t written = fwrite(ptr, size, nmemb, fp);
    return written;
}

static size_t getcontentlengthfunc(void *ptr, size_t size, size_t nmemb, void *data)
{
    return (size_t)(size * nmemb);
}

/************************************************************************/
/*
 这个回调函数可以告诉我们有多少数据需要传输以及传输了多少数据，单位是字节。
 totalToDownload是需要下载的总字节数(这里不包括本地已下载的一部分)，nowDownloaded是已经下载的字节数(指的是totalToDownload中已下载多少)。
 totalToUpLoad是将要上传的字节数，nowUpLoaded是已经上传的字节数。如果你仅仅下载数据的话，那么ultotal，ulnow将会是0，反之，
 如果你仅仅上传的话，那么dltotal和dlnow也会是0。clientp为用户自定义参数，
 通过设置CURLOPT_XFERINFODATA属性来传递。此函数返回非0值将会中断传输，错误代码是CURLE_ABORTED_BY_CALLBACK
 */
/************************************************************************/
static int callBackOnProssess(void *ptr, double totalToDownload, double nowDownloaded, double totalToUpLoad, double nowUpLoaded) {
    CURL *handle =(CURL*)ptr;
    float speed; //下载速度
    curl_easy_getinfo(handle, CURLINFO_SPEED_DOWNLOAD, &speed); // curl_get_info必须在curl_easy_perform之后调用
    //CCLOG("callBackOnProssess:%f %f %f",nowDownloaded,totalToDownload,speed);
    if(nowDownloaded && !s_download_finished){
        Director::getInstance()->getScheduler()->performFunctionInCocosThread([=](){
            s_cb_progress(nowDownloaded,totalToDownload,speed);
        });
    }
    if(nowDownloaded && totalToDownload==nowDownloaded)
        s_download_finished=true;
    return 0;
}

long CurlUtil::GetDownloadFileSize(const char*szUrl)
{
    CURL *handle = curl_easy_init();
    long fileSize=0;
    curl_easy_setopt(handle, CURLOPT_URL, szUrl);
    //curl_easy_setopt(handle, CURLOPT_HEADER, 1); //这个使libcurl会默认设置获取方式为HEAD方式，如果把set nobody的option去掉，又会下载文件内容！不可取
    curl_easy_setopt(handle, CURLOPT_CUSTOMREQUEST, "GET"); //设置为get方式获取
    curl_easy_setopt(handle, CURLOPT_NOBODY, 1);
    curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0L);
    CURLcode retCode = curl_easy_perform(handle);
    
    if(retCode==CURLE_OK){
         curl_easy_getinfo(handle, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &fileSize);
    }else{
        const char* errStr = curl_easy_strerror(retCode);
        CCLOGERROR("getDownloadFileSize:curl_easy_perform error %s",errStr);
        fileSize=-1;
    }
    curl_easy_cleanup(handle);
    //清理curl，和前面的初始化匹配
    return fileSize;
}
void static performError(const char* szErr){
    Director::getInstance()->getScheduler()->performFunctionInCocosThread([=](){
        s_cb_error(szErr);
    });
}
void static performEnd(){
    Director::getInstance()->getScheduler()->performFunctionInCocosThread([=](){
        s_cb_finished();
    });
}
void static threadDownload(std::string strUrl, std::string strSaveFileName,int timeout,bool bUseResume,std::function<void(long,long,float)> onProgress,std::function<void(void)> onEnd,std::function<void(const char*)> onError){
    FILE *fWrite = NULL;
    bool bAppend=false;
    long currentFileSize=0;
    const char* szUrl=strUrl.c_str();
    const char* saveFileName=strSaveFileName.c_str();
    if(!timeout)
        timeout=30;
    std::string saveFileNameTmp=strSaveFileName+".tmp";
    
    if(bUseResume && access(saveFileNameTmp.c_str(),0) == 0){
        fWrite = fopen(saveFileNameTmp.c_str(), "ab+");
        bAppend=true;
    }
    else
        fWrite = fopen(saveFileNameTmp.c_str(), "wb");
   
    if (fWrite == NULL) {
        const char* szErr=strerror(errno);
        CCLOGERROR("threadDownload:fopen %s for write(append %d) failed %d %s",saveFileNameTmp.c_str(),bAppend,errno,szErr);
        performError(szErr);
        return;
    }
    
    // 读取本地文件下载大小
    s_cb_progress=onProgress;
    s_cb_error=onError;
    s_cb_finished=onEnd;
    s_download_finished=false;
    if(bUseResume && bAppend){
        bool needRedownload=false;
        FILE *fRead = fopen(saveFileNameTmp.c_str(), "r");
        if (fRead == NULL) {// 如果文件初始化失败进行返回
            CCLOGERROR("threadDownload:fopen %s for read failed %d %s",saveFileNameTmp.c_str(),errno,strerror(errno));
            performError(strerror(errno));
            return;
        }
        fseek(fRead, 0, SEEK_END);
        currentFileSize = ftell(fRead);
        fclose(fRead);
        //check if file already ok
        long totalSize=CurlUtil::GetDownloadFileSize(szUrl);
        if(totalSize!=-1){
            //file is ok
            if(totalSize==currentFileSize){
                  CCLOG("threadDownload:%s exists,size is %ld=%ld,download already ok,rename then return",saveFileNameTmp.c_str(),currentFileSize,totalSize);
                rename(saveFileNameTmp.c_str(),saveFileName);
                performEnd();
                return;
            }else if(currentFileSize>totalSize){
                //file is wrong,delete and re download
                CCLOG("threadDownload:%s exists,size is %ld>%ld,delete and re-download",saveFileNameTmp.c_str(),currentFileSize,totalSize);
                needRedownload=true;
            }
        }else{
            CCLOG("threadDownload:%s GetDownloadFileSize failed",szUrl);
            needRedownload=true;
        }
        if(needRedownload){
            fclose(fWrite);
            unlink(saveFileNameTmp.c_str());
            fWrite = fopen(saveFileNameTmp.c_str(), "wb");
            if(!fWrite){
                CCLOGERROR("threadDownload:fopen %s for write failed %d %s",saveFileNameTmp.c_str(),errno,strerror(errno));
                performError(strerror(errno));
                return;
            }
            bAppend=false;
            currentFileSize=0;
        }
    }
    CCLOGERROR("threadDownload:fopen %s (append %d curSize %ld) ok", saveFileNameTmp.c_str(),bAppend,currentFileSize);
    CURL *handle = curl_easy_init();
    curl_easy_setopt(handle,CURLOPT_URL,szUrl);
    curl_easy_setopt(handle,CURLOPT_TIMEOUT,timeout);//设置下载时间，超过时间断开下载，测试模式下把这行注释可以无时间限制下载
    curl_easy_setopt(handle,CURLOPT_CONNECTTIMEOUT,10);//感觉没什么卵用,得看下
    curl_easy_setopt(handle,CURLOPT_HEADERFUNCTION,getcontentlengthfunc);
    curl_easy_setopt(handle,CURLOPT_WRITEFUNCTION,write_func);   //写文件回调方法
    curl_easy_setopt(handle,CURLOPT_WRITEDATA,fWrite); // 写入文件对象
    curl_easy_setopt(handle,CURLOPT_RESUME_FROM,currentFileSize);  // 从本地大小位置进行请求数据
    //    curl_easy_setopt(handle, CURLOPT_RESUME_FROM_LARGE, (long long)(use_resume ? localFileLenth : 0)); // CURLOPT_RESUME_FROM_LARGE针对于大文件
    curl_easy_setopt(handle,CURLOPT_NOPROGRESS,0L);
    curl_easy_setopt(handle,CURLOPT_PROGRESSFUNCTION,callBackOnProssess); //下载进度回调方法
    //curl_easy_setopt(handle, CURLOPT_PROGRESSDATA, this); // 传入本类对象
    curl_easy_setopt(handle,CURLOPT_PROGRESSDATA,handle);//将handle传入
    curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0L);
    CURLcode retCode = curl_easy_perform(handle);
    fclose(fWrite);
    if(retCode!=CURLE_OK){
        const char* errStr = curl_easy_strerror(retCode);
        CCLOGERROR("threadDownload:downloading %s failed %d %s",szUrl,retCode,errStr);
         performError(errStr);
        return;
    }
    CCLOG("threadDownload:downloading %s ok",szUrl);
    if(rename(saveFileNameTmp.c_str(),saveFileName)){
        CCLOGERROR("threadDownload:rename %s to %s failed %d %s",saveFileNameTmp.c_str(),saveFileName,errno,strerror(errno));
        performError(strerror(errno));
    }else{
        CCLOG("threadDownload:rename %s to %s ok",saveFileNameTmp.c_str(),saveFileName);
        performEnd();
    }
}

void CurlUtil::Download(const char *szUrl, const char *saveFileName,int timeout,bool bUseResume,std::function<void(long curSize,long totalSize,float speed)> cbProgress,std::function<void(void)> cbEnd,std::function<void(const char* szErr)> cbError){
    std::thread doJob(threadDownload,std::string(szUrl),std::string(saveFileName),timeout,bUseResume,cbProgress,cbEnd,cbError);
    doJob.detach();
}
