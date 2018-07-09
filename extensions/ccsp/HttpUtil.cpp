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

bool HttpUtil::post(const char *szUrl, const char *szParam,const char* szFileName,[=]<std::string retStr>()){
    //The url where you have the server side upload script
    std::string url = "http://XXX.XXX.XXX.XXX/upload.php";
    
    
    //The basename is the whatever you use in the server side as 'file' id
    //I think can be 'uploadedfile'
    //or whatever as long as it'll be the same in both sides (client/server)
    //in php:
    //$_FILES['file']['name']
    //$_FILES['file']['tmp_name']
    
    std::string strFileName(szFileName);
    std::string baseName=strFileName.substr(strFileName.find_last_of('/'));
    long bufferSize = 0;
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
    request->setTag("UPLOAD FILE");
    
    //Check that everything went OK when the request response calls your app back:
    request->setResponseCallback( [=]
                                 (network::HttpClient* client,
                                  network::HttpResponse* response)
                                 {
                                     int returnCode=(int)response->getResponseCode();
                                      printf("HttpUtil::post Response Code %d\n", returnCode);
                                     if (returnCode==200){
                                         printf("HttpUtil::post OK\n");
                                         std::vector<char> *buffer = response->getResponseData();
                                         printf("HttpUtil::post Get data from server:\n");
                                         //                                     for (unsigned int i = 0; i < buffer->size(); i++)
                                         //                                     { printf("%c", (*buffer)[i]); }
                                         
                                
                                         std::string retStr=response->getResponseDataString();
                                         
                                         printf("HttpUtil::post Response Code %li   ", response->getResponseCode());
                                     }
                                     else{
                                         printf("HttpUtil::post failed\n");
                                     }
                                     
                                    
                                     
                                 });
    
    //Finally send the request:
    cocos2d::network::HttpClient::getInstance()->send(request);
    
    //And then get rid of it:
    request->release();
    return true;
}
