//
//  UIUtil.cpp
//  cocos2d_libs
//
//  Created by joe on 2017/8/15.
//
//



#include <stdio.h>
#include "UIUtil.h"

using namespace ccsp;
using namespace cocos2d;
static UIUtil* s_instance=NULL;

UIUtil* UIUtil::getInstance(){
    if(!s_instance){
        s_instance=new UIUtil();
    }
    return s_instance;
}

Node* UIUtil::seekNodeByName(Node* root, const std::string& name)
{
    if (!root)
    {
        return nullptr;
    }
    if (root->getName() == name)
    {
        return root;
    }
    const auto& arrayRootChildren = root->getChildren();
    for (auto& subWidget : arrayRootChildren)
    {
        Node* child = dynamic_cast<Node*>(subWidget);
        if (child)
        {
            Node* res = seekNodeByName(child,name);
            if (res != nullptr)
            {
                return res;
            }
        }
    }
    return nullptr;
}
