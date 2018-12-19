//
//  VersionUtil.cpp
//  cocos2d_libs
//
//  Created by joe on 2017/7/19.
//
//

#include "VersionUtil.h"

#include <sstream>
#include <iostream>
#include <regex>
#include "cocos2d.h"

using namespace ccsp;

int VersionUtil::compare(std::string strV1,std::string strV2){
    int v1Arr[10]={0};
    int v2Arr[10]={0};
    int i=0;
    int j=0;
    
 	if(!strV1.size() && !strV2.size())   
 		return 0;
 	if(!strV1.size() || !strV2.size())   
 		return -1;
 	if(!strV1.compare(strV2))
 		return 0;

    std::regex re("\\d+\\.*");
 	std::cout.setf(std::ios_base::boolalpha);
 	std::smatch result1;
    std::smatch result2;
 	if(!std::regex_search(strV1,result1,re))
 		return -1;
	if(!std::regex_search(strV2,result2,re))
 		return -1;

    std::regex_iterator<std::string::const_iterator> begin1(strV1.cbegin(), strV1.cend(), re);
    for (auto iter = begin1; iter != std::sregex_iterator(); iter++)
    {
        int v=atoi(iter->str().c_str());
        v1Arr[i++]=v;
        if(i>=10)
            return -1;
        //CCLOG("find-1 %s %d",iter->str().c_str(),v);
    }
    
    std::regex_iterator<std::string::const_iterator> begin2(strV2.cbegin(), strV2.cend(), re);
    for (auto iter = begin2; iter != std::sregex_iterator(); iter++)
    {
        int v=atoi(iter->str().c_str());
        v2Arr[j++]=v;
        if(j>=10)
            return -1;
        //CCLOG("find-2 %s %d",iter->str().c_str(),v);
    }
    
    if(i!=j)
        return -1;
    
    for (int m=0;m<i;m++)
	{

        int v1=v1Arr[m];
        int v2=v2Arr[m];
		if(v1==v2)
			continue;
		else if(v1>v2)
			return 1;
		else if(v1<v2)
			return -1;
	}
    return -1;
}
