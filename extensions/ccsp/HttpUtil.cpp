//
//  HttpUtil.cpp
//  cocos2d_libs
//
//  Created by Joe on 2018/7/9.
//

#include "HttpUtil.h"
#include "cocos2d.h"
#include "HttpClient.h"


using namespace ccsp;
using namespace cocos2d;

bool HttpUtil::upload(const char *szUrl,const char* szFileName,std::function<void(int code,const char* strResponse)> cb){
    std::string strFileName(szFileName);
    std::string baseName=strFileName.substr(strFileName.find_last_of('/')+1);
    ssize_t bufferSize = 0;
    unsigned char* pBuffer = FileUtils::getInstance()->getFileData(szFileName, "r", &bufferSize);
    //The same file stored as a string of "bytes" (it may contain zeroes)
    std::string data = std::string((const char*)pBuffer, bufferSize);
    //Create an http post request
    network::HttpRequest *request = new network::HttpRequest();
    request->setUrl(szUrl);
    request->setRequestType(cocos2d::network::HttpRequest::Type::POST);
    //Include this boundary in the header and in the body of the request
    std::string boundary = "---------------------------1473780983146649988274664144900";
    //The content of the request must be multipart/form-data
    std::vector<std::string> contentType;
    contentType.push_back("Content-Type: multipart/form-data; boundary=" + boundary);
    //Set the header with the previous content type
    request->setHeaders(contentType);
    //Build the body of the request. Include the boundary, basename and file name.
    //Specify the content disposition and type
    std::string body = "\r\n--" + boundary + "\r\n";
    body = body + "Content-Disposition: form-data; name=\"" + baseName
    + "\"; filename=\"" + baseName + "\"\r\n";
    body = body + "Content-Type: application/octet-stream\r\n\r\n";
    //Then append the file data and again the boundary
    body = body + data;
    body = body + "\r\n--" + boundary + "--\r\n";
    request->setRequestData(body.data(), body.size());
    //Just a tag...
    request->setTag("ccsp_HttpUtil_upload");
    //Check that everything went OK when the request response calls your app back:
    request->setResponseCallback( [=](network::HttpClient* client,network::HttpResponse* response)
                                 {
                                     std::string strRet;
                                     int returnCode=(int)response->getResponseCode();
                                     if (returnCode==200){
                                         std::vector<char> *buffer = response->getResponseData();
                                         strRet.assign(buffer->begin(),buffer->end());
                                     }
                                     Director::getInstance()->getScheduler()->performFunctionInCocosThread([=](){
                                         cb(returnCode,strRet.c_str());
                                     });
                                 }
    );
    //Finally send the request:
    cocos2d::network::HttpClient::getInstance()->send(request);
    //And then get rid of it:
    request->release();
    return true;
}

bool HttpUtil::post(const char *szUrl,std::function<void(int code,const char* strResponse)> cb){
    network::HttpRequest *request = new network::HttpRequest();
    request->setUrl(szUrl);
    request->setRequestType(cocos2d::network::HttpRequest::Type::POST);
    request->setTag("ccsp_HttpUtil_post");
    request->setResponseCallback( [=](network::HttpClient* client,network::HttpResponse* response)
                                 {
                                     std::string strRet;
                                     int returnCode=(int)response->getResponseCode();
                                     if (returnCode==200){
                                         std::vector<char> *buffer = response->getResponseData();
                                         strRet.assign(buffer->begin(),buffer->end());
                                     }
                                     Director::getInstance()->getScheduler()->performFunctionInCocosThread([=](){
                                         cb(returnCode,strRet.c_str());
                                     });
                                 }
                                 );
  
    cocos2d::network::HttpClient::getInstance()->send(request);
    request->release();
    return true;
}


bool HttpUtil::get(const char *szUrl,std::function<void(int code,const char* strResponse)> cb){
    network::HttpRequest *request = new network::HttpRequest();
    request->setUrl(szUrl);
    request->setRequestType(cocos2d::network::HttpRequest::Type::GET);
    request->setTag("ccsp_HttpUtil_get");
    request->setResponseCallback( [=](network::HttpClient* client,network::HttpResponse* response)
                                 {
                                     std::string strRet;
                                     int returnCode=(int)response->getResponseCode();
                                     if (returnCode==200){
                                         std::vector<char> *buffer = response->getResponseData();
                                         strRet.assign(buffer->begin(),buffer->end());
                                     }else{
                                         CCLOG("HttpUtil::get:error %s,code %d",response->getErrorBuffer(),returnCode);
                                     }
                                     Director::getInstance()->getScheduler()->performFunctionInCocosThread([=](){
                                         cb(returnCode,strRet.c_str());
                                     });
                                 }
                                 );
    cocos2d::network::HttpClient::getInstance()->send(request);
    request->release();
    return true;
}
