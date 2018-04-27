//
//  XPRichText.cpp
//  cocos2d_libs
//
//  Created by Joe on 2018/4/24.
//




#include "XPRichText.h"
//#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <locale>


#include "platform/CCFileUtils.h"
#include "platform/CCApplication.h"
#include "base/CCEventListenerTouch.h"
#include "base/CCEventDispatcher.h"
#include "base/CCDirector.h"
#include "2d/CCLabel.h"
#include "2d/CCSprite.h"
#include "base/ccUTF8.h"
#include "ui/UIHelper.h"
//#include "platform/CCSAXParser.h"

//#include "ui/UIRichText.h"
#include "StrUtil.h"

//USING_NS_CC;
using namespace cocos2d;
using namespace cocos2d::ui;

//using namespace std;

using namespace ccsp;


XPRichText::XPRichText(float linneInner,Size fixedSize,TextHAlignment alignH,TextVAlignment alignV,int newLinePolicy,bool debug)
: _formatTextDirty(true)
, _leftSpaceWidth(0.0f)
{
    _lineInner=linneInner;
    _fixWidth=fixedSize.width;
    _fixHeight=fixedSize.height;
    _alignH=alignH;
    _alignV=alignV;
    _newLinePolicy=newLinePolicy;
    _debug=debug;
}

XPRichText::~XPRichText()
{
    _richElements.clear();

    for (auto& iter : _elementRenders)
    {
        iter->clear();
        delete iter;
    }
    _elementRenders.clear();
}

XPRichText* XPRichText::create(float linneInner,Size fixedSize,TextHAlignment alignH,TextVAlignment alignV,int newLinePolicy,bool debug)
{
    XPRichText* widget = new (std::nothrow) XPRichText(linneInner,fixedSize,alignH,alignV,newLinePolicy,debug);
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}

bool XPRichText::init()
{
    if (Widget::init())
        return true;
    return false;
}

void XPRichText::initRenderer()
{
    if(_debug){
        _drawNode=DrawNode::create();
         addChild(_drawNode,1,-1);
        _backLayer=LayerColor::create(Color4B(255,0,0,50));
        addChild(_backLayer,0,-1);
    }
}

void XPRichText::pushToContainer(int index,cocos2d::Node *renderer)
{
    if (_elementRenders.size() <= 0)
        _elementRenders.push_back(new Vector<Node*>());
    if(index==_elementRenders.size())
         _elementRenders.push_back(new Vector<Node*>());
    if(index>_elementRenders.size())
        return;
    _elementRenders[index]->pushBack(renderer);
}

void XPRichText::addNewLine()
{
    _leftSpaceWidth = _fixWidth;
    _elementRenders.push_back(new Vector<Node*>());
}

void XPRichText::pushBackElement(RichElement *element)
{
    _richElements.pushBack(element);
    _formatTextDirty = true;
}

void XPRichText::formatText()
{
    if (_formatTextDirty)
    {
        this->removeAllProtectedChildren();
        for (auto& iter : _elementRenders)
        {
            iter->clear();
            delete iter;
        }
        _elementRenders.clear();
        int index=0;
        if (!_fixWidth)
        {
           //auto size
            for (ssize_t i=0, size = _richElements.size(); i<size; ++i)
            {
                RichElement* element = _richElements.at(i);
                Node* elementRenderer = nullptr;
                switch (element->_type)
                {
                    case RichElement::Type::TEXT:
                    {
                        RichElementText* elmtText = static_cast<RichElementText*>(element);
                        if(elmtText->_text=="\n"){
                            addNewLine();
                            index++;
                            continue;
                        }
                        cocos2d::Label* label;
                        if (FileUtils::getInstance()->isFileExist(elmtText->_fontName))
                        {
                            label = cocos2d::Label::createWithTTF(elmtText->_text, elmtText->_fontName, elmtText->_fontSize);
                        }
                        else
                        {
                            label = cocos2d::Label::createWithSystemFont(elmtText->_text, elmtText->_fontName, elmtText->_fontSize);
                        }
                        if(elmtText->_flags){
                            if (elmtText->_flags & RichElementText::ITALICS_FLAG)
                                label->enableItalics();
                            if (elmtText->_flags & RichElementText::BOLD_FLAG)
                                label->enableBold();
                            if (elmtText->_flags & RichElementText::UNDERLINE_FLAG)
                                label->enableUnderline();
                            if (elmtText->_flags & RichElementText::STRIKETHROUGH_FLAG)
                                label->enableStrikethrough();
                            //                        if (elmtText->_flags & RichElementText::URL_FLAG)
                            //                            label->addComponent(cocos2d::ui::ListenerComponent::create(label, elmtText->_url,
                            //                                                                          std::bind(&XPRichText::openUrl, this, std::placeholders::_1)));
                            if (elmtText->_flags & RichElementText::OUTLINE_FLAG) {
                                label->enableOutline(Color4B(elmtText->_outlineColor), elmtText->_outlineSize);
                            }
                            if (elmtText->_flags & RichElementText::SHADOW_FLAG) {
                                label->enableShadow(Color4B(elmtText->_shadowColor),
                                                    elmtText->_shadowOffset,
                                                    elmtText->_shadowBlurRadius);
                            }
                            if (elmtText->_flags & RichElementText::GLOW_FLAG) {
                                label->enableGlow(Color4B(elmtText->_glowColor));
                            }
                        }
                     
                        elementRenderer = label;
                        break;
                    }
                    case RichElement::Type::IMAGE:
                    {
                        RichElementImage* elmtImage = static_cast<RichElementImage*>(element);
                        if(elmtImage->_filePath[0]=='#')
                            elementRenderer = Sprite::createWithSpriteFrameName(elmtImage->_filePath.substr(1,elmtImage->_filePath.length()));
                        else
                            elementRenderer = Sprite::create(elmtImage->_filePath);
                        if (elementRenderer && (elmtImage->_height != -1 || elmtImage->_width != -1))
                        {
                            auto currentSize = elementRenderer->getContentSize();
                            if (elmtImage->_width != -1)
                                elementRenderer->setScaleX(elmtImage->_width / currentSize.width);
                            if (elmtImage->_height != -1)
                                elementRenderer->setScaleY(elmtImage->_height / currentSize.height);
                            elementRenderer->setContentSize(Size(currentSize.width * elementRenderer->getScaleX(),
                                                                 currentSize.height * elementRenderer->getScaleY()));
//                            elementRenderer->addComponent(ListenerComponent::create(elementRenderer,
//                                                                                    elmtImage->_url,
//                                                                                    std::bind(&XPRichText::openUrl, this, std::placeholders::_1)));
                        }
                        break;
                    }
                    case RichElement::Type::CUSTOM:
                    {
                        RichElementCustomNode* elmtCustom = static_cast<RichElementCustomNode*>(element);
                        elementRenderer = elmtCustom->_customNode;
                        break;
                    }
                    case RichElement::Type::NEWLINE:
                    {
                        addNewLine();
                         index++;
                        break;
                    }
                    default:
                        break;
                }

                if (elementRenderer)
                {
                    elementRenderer->setAnchorPoint(Point(0,0));
                    elementRenderer->setIgnoreAnchorPointForPosition(false);
                    elementRenderer->setColor(element->_color);
                    elementRenderer->setOpacity(element->_opacity);
                    pushToContainer(index,elementRenderer);
                }
            }
        }
        else
        {
            //fixed size
            _leftSpaceWidth=_fixWidth;
            for (ssize_t i=0, size = _richElements.size(); i<size; ++i)
            {
                RichElement* element = static_cast<RichElement*>(_richElements.at(i));
                switch (element->_type)
                {
                    case RichElement::Type::TEXT:
                    {
                        RichElementText* elmtText = static_cast<RichElementText*>(element);
                        if(elmtText->_text=="\n"){
                            addNewLine();
                            index++;
                            continue;
                        }
                        
                        std::vector<std::string> textArr=StrUtil::explode(elmtText->_text,'\n');
                        unsigned long m=textArr.size();
                        for(int j=0;j<m;j++){
                            index=handleTextRenderer(index,textArr.at(j), elmtText->_fontName, elmtText->_fontSize, elmtText->_color,elmtText->_opacity, elmtText->_flags, elmtText->_url,elmtText->_outlineColor, elmtText->_outlineSize,elmtText->_shadowColor, elmtText->_shadowOffset, elmtText->_shadowBlurRadius,elmtText->_glowColor);
                            if(m>=2 && j!=m-1){
                                addNewLine();
                                index++;
                            }
                        }
                        break;
                    }
                    case RichElement::Type::IMAGE:
                    {
                        RichElementImage* elmtImage = static_cast<RichElementImage*>(element);
                        index=handleImageRenderer(index,elmtImage->_filePath, elmtImage->_color, elmtImage->_opacity, elmtImage->_width, elmtImage->_height, elmtImage->_url);
                        break;
                    }
                    case RichElement::Type::CUSTOM:
                    {
                        RichElementCustomNode* elmtCustom = static_cast<RichElementCustomNode*>(element);
                        index=handleCustomRenderer(index,elmtCustom->_customNode);
                        break;
                    }
                    case RichElement::Type::NEWLINE:
                    {
                        addNewLine();
                        index++;
                        break;
                    }
                    default:
                        break;
                }
            }
        }
        formarRenderers();
        _formatTextDirty = false;
    }
}

static int getPrevWord(const std::string& text, int idx)
{
    // start from idx-1
    for (int i=idx-1; i>=0; --i)
    {
        if (!std::isalnum(text[i], std::locale()))
            return i;
    }
    return -1;
}

static bool isWrappable(const std::string& text)
{
    for (size_t i = 0, size = text.length(); i < size; ++i)
    {
        if (!std::isalnum(text[i], std::locale()))
            return true;
    }
    return false;
}

int XPRichText::findSplitPositionForWord(cocos2d::Label* label, const std::string& text)
{
    auto originalLeftSpaceWidth = _leftSpaceWidth + label->getContentSize().width;

    bool startingNewLine = (_customSize.width == originalLeftSpaceWidth);
    if (!isWrappable(text))
    {
        if (startingNewLine)
            return (int) text.length();
        return 0;
    }

    for(int idx = (int)text.size()-1; idx >=0; )
    {
        int newidx = getPrevWord(text, idx);
        if (newidx >=0)
        {
            idx = newidx;
            auto leftStr = Helper::getSubStringOfUTF8String(text, 0, idx);
            label->setString(leftStr);
            if (label->getContentSize().width <= originalLeftSpaceWidth)
                return idx;
        }
        else
        {
            if (startingNewLine)
                return idx;
            return 0;
        }
    }

    // no spaces... return the original label + size
    label->setString(text);
    return (int)text.size();
}

int XPRichText::handleTextRenderer(int index,const std::string& text, const std::string& fontName, float fontSize, const Color3B &color,
                                  GLubyte opacity, uint32_t flags, const std::string& url,
                                  const Color3B& outlineColor, int outlineSize ,
                                  const Color3B& shadowColor, const cocos2d::Size& shadowOffset, int shadowBlurRadius,
                                  const Color3B& glowColor)
{
    if(text=="")
        return index;
    auto fileExist = FileUtils::getInstance()->isFileExist(fontName);
    cocos2d::Label* textRenderer = nullptr;
    if (fileExist)
    {
        textRenderer = cocos2d::Label::createWithTTF(text, fontName, fontSize);
    }
    else
    {
        textRenderer = cocos2d::Label::createWithSystemFont(text, fontName, fontSize);
    }
    if (flags & RichElementText::ITALICS_FLAG)
        textRenderer->enableItalics();
    if (flags & RichElementText::BOLD_FLAG)
        textRenderer->enableBold();
    if (flags & RichElementText::UNDERLINE_FLAG)
        textRenderer->enableUnderline();
    if (flags & RichElementText::STRIKETHROUGH_FLAG)
        textRenderer->enableStrikethrough();
//    if (flags & RichElementText::URL_FLAG)
//        textRenderer->addComponent(ListenerComponent::create(textRenderer,
//                                                             url,
//                                                             std::bind(&RichText::openUrl, this, std::placeholders::_1)));
    if (flags & RichElementText::OUTLINE_FLAG) {
        textRenderer->enableOutline(Color4B(outlineColor), outlineSize);
    }
    if (flags & RichElementText::SHADOW_FLAG) {
        textRenderer->enableShadow(Color4B(shadowColor), shadowOffset, shadowBlurRadius);
    }
    if (flags & RichElementText::GLOW_FLAG) {
        textRenderer->enableGlow(Color4B(glowColor));
    }

    float textRendererWidth = textRenderer->getContentSize().width;
    _leftSpaceWidth -= textRendererWidth;
    if (_leftSpaceWidth < 0.0f)
    {
        int leftLength = 0;
         leftLength = findSplitPositionForWord(textRenderer, text);
        
//        if (static_cast<RichText::WrapMode>(_defaults.at(KEY_WRAP_MODE).asInt()) == WRAP_PER_WORD)
//            leftLength = findSplitPositionForWord(textRenderer, text);
//        else
//            leftLength = findSplitPositionForChar(textRenderer, text);

        //The minimum cut length is 1, otherwise will cause the infinite loop.
        //        if (0 == leftLength) leftLength = 1;
        std::string leftWords = Helper::getSubStringOfUTF8String(text, 0, leftLength);
        int rightStart = leftLength;
        if (std::isspace(text[rightStart], std::locale()))
            rightStart++;
        std::string cutWords = Helper::getSubStringOfUTF8String(text, rightStart, text.length() - leftLength);
        if (leftLength > 0)
        {
            cocos2d::Label* leftRenderer = nullptr;
            if (fileExist)
            {
                leftRenderer = cocos2d::Label::createWithTTF(Helper::getSubStringOfUTF8String(leftWords, 0, leftLength), fontName, fontSize);
            }
            else
            {
                leftRenderer = cocos2d::Label::createWithSystemFont(Helper::getSubStringOfUTF8String(leftWords, 0, leftLength), fontName, fontSize);
            }
            if (leftRenderer)
            {
                leftRenderer->setAnchorPoint(Point(0,0));
                leftRenderer->setIgnoreAnchorPointForPosition(false);
                leftRenderer->setColor(color);
                leftRenderer->setOpacity(opacity);
                pushToContainer(index,leftRenderer);

                if(flags){
                    if (flags & RichElementText::ITALICS_FLAG)
                        leftRenderer->enableItalics();
                    if (flags & RichElementText::BOLD_FLAG)
                        leftRenderer->enableBold();
                    if (flags & RichElementText::UNDERLINE_FLAG)
                        leftRenderer->enableUnderline();
                    if (flags & RichElementText::STRIKETHROUGH_FLAG)
                        leftRenderer->enableStrikethrough();
                    //                if (flags & RichElementText::URL_FLAG)
                    //                    leftRenderer->addComponent(ListenerComponent::create(leftRenderer,
                    //                                                                         url,
                    //                                                                         std::bind(&RichText::openUrl, this, std::placeholders::_1)));
                    if (flags & RichElementText::OUTLINE_FLAG) {
                        leftRenderer->enableOutline(Color4B(outlineColor), outlineSize);
                    }
                    if (flags & RichElementText::SHADOW_FLAG) {
                        leftRenderer->enableShadow(Color4B(shadowColor), shadowOffset, shadowBlurRadius);
                    }
                    if (flags & RichElementText::GLOW_FLAG) {
                        leftRenderer->enableGlow(Color4B(glowColor));
                    }
                }
            }
        }

        addNewLine();
        return handleTextRenderer(index+1,cutWords, fontName, fontSize, color, opacity, flags, url,
                           outlineColor, outlineSize,
                           shadowColor, shadowOffset, shadowBlurRadius,
                           glowColor);
    }
    else
    {
        textRenderer->setColor(color);
        textRenderer->setOpacity(opacity);
        pushToContainer(index,textRenderer);
        return index;
    }
}

int XPRichText::handleImageRenderer(int index,const std::string& filePath, const Color3B &/*color*/, GLubyte /*opacity*/, int width, int height, const std::string& url)
{
    Sprite* imageRenderer;
    if(filePath[0]=='#')
        imageRenderer = Sprite::createWithSpriteFrameName(filePath.substr(1,filePath.length()));
    else
        imageRenderer = Sprite::create(filePath);
    ///Sprite* imageRenderer = Sprite::create(filePath);
    if (imageRenderer)
    {
        auto currentSize = imageRenderer->getContentSize();
        if (width != -1)
            imageRenderer->setScaleX(width / currentSize.width);
        if (height != -1)
            imageRenderer->setScaleY(height / currentSize.height);
        imageRenderer->setContentSize(Size(currentSize.width * imageRenderer->getScaleX(),
                                           currentSize.height * imageRenderer->getScaleY()));

        return handleCustomRenderer(index,imageRenderer);
//        imageRenderer->addComponent(ListenerComponent::create(imageRenderer,
//                                                              url,
//                                                              std::bind(&RichText::openUrl, this, std::placeholders::_1)));
    }
    return index;
}

int XPRichText::handleCustomRenderer(int index,cocos2d::Node *renderer)
{
    renderer->setAnchorPoint(Point(0,0));
    renderer->setIgnoreAnchorPointForPosition(false);
    Size imgSize = renderer->getContentSize();
    _leftSpaceWidth -= imgSize.width;
    if (_leftSpaceWidth < 0.0f)
    {
        addNewLine();
        index++;
        pushToContainer(index,renderer);
        _leftSpaceWidth -= imgSize.width;
    }
    else
    {
        pushToContainer(index,renderer);
    }
    return index;
}

float XPRichText::_findMaxHeightInAllRenders(){
    float max=0;
    for(auto& row:_elementRenders){
        if(!row->size())
            continue;
        for(auto& node:*row){
            float h=node->getContentSize().height;
            if(h>max)
                max=h;
        }
    }
    return max;
}

float XPRichText::_getLineHeight(Vector<Node*>* arr){
    float max=0;
    for(auto& node:*arr){
        float h=node->getContentSize().height;
        if(h>max)
            max=h;
    }
    return max;
}

float XPRichText::_getLineWidth(Vector<Node*>* arr){
    float v=0;
    for(auto& node:*arr){
        v+=node->getContentSize().width;
    }
    return v;
}
float XPRichText::_findMaxLineWidth(){
    float max=0;
    for(auto& row:_elementRenders){
        if(!row->size())
            continue;
        float w=_getLineWidth(row);
        if(w>max)
            max=w;
    }
    return max;
}

float XPRichText::_formatOneLine(Vector<Node*>* arr,TextHAlignment alignH,TextVAlignment alignV,float offsetY){
    float lineHeight=_getLineHeight(arr);
    float maxLineWidth=0;
    if(_maxLineWidth)
        maxLineWidth=_maxLineWidth;
    else if(_fixWidth){
        maxLineWidth=_fixWidth;
        _maxLineWidth=maxLineWidth;
    }
    else{
        maxLineWidth=_findMaxLineWidth();
        _maxLineWidth=maxLineWidth;
    }
    
    float lineWidth=_getLineWidth(arr);
    float x=0;
    float y=0;
    float lastX=0;
    if(alignH==TextHAlignment::LEFT)
        lastX=0;
    else if(alignH==TextHAlignment::RIGHT)
        lastX=maxLineWidth-lineWidth;
    else
        lastX=(maxLineWidth-lineWidth)/2;
    
    for(int i=0,l=(int)arr->size();i<l;i++){
        Node* render=arr->at(i);
        render->setAnchorPoint(Point(0,0));
        render->setIgnoreAnchorPointForPosition(false);
        Size renderSize=render->getContentSize();
        if(alignV==TextVAlignment::BOTTOM)
            y=-lineHeight;
        else if(alignV==TextVAlignment::TOP)
            y=-renderSize.height;
        else{
            y=-(lineHeight+renderSize.height)/2;
            //y=-renderSize.height-(lineHeight-renderSize.height)/2;
        }
        
    
        x=lastX;
        lastX+=renderSize.width;
        render->setPosition(Point(x,y+offsetY));
    }
    return lineHeight;
}

void XPRichText::_adjustPositionY(float v){
    for(auto& row:_elementRenders){
        if(!row->size())
            continue;
        for(auto& node:*row)
            node->setPositionY(node->getPositionY()+v);
    }
}

Node* XPRichText::_getHighestRenderInLine(Vector<Node*>* arr){
    float max=0;
    Node* nodeRet=nullptr;
    for(auto& node:*arr){
        float h=node->getContentSize().height;
        if(h>max){
            max=h;
            nodeRet=node;
        }
        
    }
    return nodeRet;
}


void XPRichText::_addAllRenders(){
    int k=0;
    for(auto& row:_elementRenders){
        if(!row->size())
            continue;
        for(auto& node:*row)
            addProtectedChild(node,1,k++);
    }
}

void XPRichText::_debugDrawOneLine(Vector<Node*>* arr,float offsetX,float offsetY){
    float lineWidth=_getLineWidth(arr);
    float lineHeight=_getLineHeight(arr);
    Point p1=Point(0+offsetX,0+offsetY);
    //Point p2=Point(lineWidth+offsetX,0+offsetY);
    Point p3=Point(lineWidth+offsetX,lineHeight+offsetY);
    //Point p4=Point(0+offsetX,lineHeight+offsetY);
    _drawNode->drawRect(p1,p3,Color4F::GREEN);
    
    Point pLeft=Point(0+offsetX,lineHeight/2+offsetY);
    Point pRight=Point(lineWidth+offsetX,lineHeight/2+offsetY);
    _drawNode->drawLine(pLeft,pRight,Color4F::GREEN);
}

void XPRichText::_debugDrawAllLines(){
    for(auto& row:_elementRenders){
        if(!row->size())
            continue;
        Node* node=_getHighestRenderInLine(row);
        _debugDrawOneLine(row, row->at(0)->getPositionX(), node->getPositionY());
    }
}


Node* XPRichText::getRenderByID(int i){
    return getProtectedChildByTag(i);
}

void XPRichText::formarRenderers(){
    float maxLineHeight=_findMaxHeightInAllRenders();
    float offsetY=0;
    float innerOffsetY=0;
    float lastLineHeight=0;
    int i=0;
    int l=(int)_elementRenders.size();
    for(auto& row:_elementRenders){
        i++;
        if(!row->size()){
            if(!_newLinePolicy)
                offsetY-=maxLineHeight+_lineInner;
            else
                 offsetY-=lastLineHeight+_lineInner;
            continue;
        }
        float newLineHeight=0;
        float lineHeight=_getLineHeight(row);
        if(!_newLinePolicy){
            if(_alignV==TextVAlignment::TOP){
                
            }else if(_alignV==TextVAlignment::BOTTOM){
                innerOffsetY=maxLineHeight-lineHeight;
            }else{
                innerOffsetY=(maxLineHeight-lineHeight)/2;
            }
        }
        lineHeight=_formatOneLine(row,_alignH,_alignV,offsetY-innerOffsetY);
        lastLineHeight=lineHeight;
        
        if(!_newLinePolicy)
            newLineHeight=maxLineHeight;
        else
            newLineHeight=lastLineHeight;
        
        //if line inner is set and not the last line,should add inner
        if(_lineInner && i!=l)
            newLineHeight+=_lineInner;
        
        offsetY-=newLineHeight;
    }
   
    float adjustY=0;
    float contentWidth=0;
    float contentHeight=0;
    
    if(_fixWidth)
        contentWidth=_fixWidth;
    else
        contentWidth=_maxLineWidth;
    
    if(_fixHeight){
        contentHeight=_fixHeight;
        if(_alignV==TextVAlignment::TOP)
            adjustY=_fixHeight;
        else if(_alignV==TextVAlignment::BOTTOM)
            adjustY=-offsetY;
        else
            adjustY=(-offsetY+_fixHeight)/2;
    }else{
        contentHeight=-offsetY;
        adjustY=-offsetY;
    }
    
    _adjustPositionY(adjustY);
    Size newSize=Size(contentWidth,contentHeight);
    _addAllRenders();
    _updateClickArea();
    setContentSize(newSize);
    updateContentSizeWithTextureSize(newSize);
    
    if(_debug){
        _debugDrawAllLines();
        _backLayer->setContentSize(newSize);
    }
    
}


void XPRichText::adaptRenderers()
{
    this->formatText();
}

void XPRichText::_updateClickArea(){
    std::vector<std::tuple<Rect,std::function<void(Node*,Point)>,Node*,int>> updatedClickArea;
    for(auto info:_clickAreaArr){
        int i=std::get<3>(info);
        auto obj=getRenderByID(i);
        Size size=obj->getContentSize();
        Point pos=obj->getPosition();
        updatedClickArea.push_back(std::make_tuple(Rect(pos.x,pos.y,size.width,size.height), std::get<1>(info),obj,i));
    }
    _clickAreaArr.clear();
    _clickAreaArr=updatedClickArea;
}
void XPRichText::_onClick(Ref* sender){
    Point pos=getTouchEndPosition();
    Point pos2=convertToNodeSpace(pos);
    for(auto info:_clickAreaArr){
        Rect area;
        std::function<void(Node* node,Point p)> cb;
        Node* renderer;
        int index;
        
        std::tie(area,cb,renderer,index)=info;
        
        //auto renderer=std::get<2>(info);
        if(renderer==nullptr || !renderer->isVisible())
            continue;
        //auto area=std::get<0>(info);
        if(!area.size.width || !area.size.height)
            continue;
        if(area.containsPoint(pos2))
            //std::get<1>(info)(renderer,pos2);
            cb(renderer,pos2);
    }
}

void XPRichText::_initClick(){
    if(!_clickEnabled){
        _clickEnabled=true;
        setTouchEnabled(true);
        addClickEventListener(CC_CALLBACK_1(XPRichText::_onClick,this));
    }
}

void XPRichText::addClickEventForRenderer(int i, std::function<void(Node* node,Point p)> cb){
    if(!_clickEnabled)
        _initClick();
    Node* node=getRenderByID(i);
    if(node){
        Point pos=node->getPosition();
        Size size=node->getContentSize();
        if(size.width && size.height){
            _clickAreaArr.push_back(std::make_tuple(Rect(pos.x,pos.y,size.width,size.height),cb,node,i));
            return;
        }
    }
    _clickAreaArr.push_back(std::make_tuple(Rect(0,0,0,0),cb,nullptr,i));
}

void XPRichText::setRenderString(int index, std::string str){
    Node* node=getRenderByID(index);
    cocos2d::Label* obj=dynamic_cast<cocos2d::Label*>(node);
    if(!obj){
        CCLOG("richText.setRenderString:cannot find render by given index %d",index);
        return;
    }
    Size oldSize=obj->getContentSize();
    obj->setString(str);
    Size newSize=obj->getContentSize();

    if(!oldSize.equals(newSize)){
        if(_alignH==TextHAlignment::CENTER){
            obj->setPositionX(obj->getPositionX()-(newSize.width-oldSize.width)/2);
        }else if(_alignH==TextHAlignment::RIGHT){
            obj->setPositionX(obj->getPositionX()-(newSize.width-oldSize.width));
        }
    }
}

void XPRichText::setRenderString(int index, std::string str,Color4B color){
    Node* node=getRenderByID(index);
    cocos2d::Label* obj=dynamic_cast<cocos2d::Label*>(node);
    if(!obj){
        CCLOG("richText.setRenderString:cannot find render by given index %d",index);
        return;
    }
    Size oldSize=obj->getContentSize();
    obj->setString(str);
    Size newSize=obj->getContentSize();
    
    if(color!=obj->getTextColor())
        obj->setTextColor(color);
    
    if(!oldSize.equals(newSize)){
        if(_alignH==TextHAlignment::CENTER){
            obj->setPositionX(obj->getPositionX()-(newSize.width-oldSize.width)/2);
        }else if(_alignH==TextHAlignment::RIGHT){
            obj->setPositionX(obj->getPositionX()-(newSize.width-oldSize.width));
        }
    }
}

void XPRichText::setRenderTexture(int index, std::string texturePath){
    Node* node=getRenderByID(index);
    cocos2d::Sprite* obj=dynamic_cast<cocos2d::Sprite*>(node);
    if(!obj){
        CCLOG("setRenderTexture:cannot find render by given index %d",index);
        return;
    }
    
    if(texturePath[0]=='#')
        obj->setSpriteFrame(texturePath.substr(1,texturePath.length()-1));
    else
        obj->setTexture(texturePath);
}

std::string XPRichText::getDescription() const
{
    return "XPRichText";
}

void XPRichText::openUrl(const std::string& url)
{
    if (_handleOpenUrl) {
        _handleOpenUrl(url);
    }
    else {
        Application::getInstance()->openURL(url);
    }
}

void XPRichText::setOpenUrlHandler(const OpenUrlHandler& handleOpenUrl)
{
    _handleOpenUrl = handleOpenUrl;
}

//void XPRichText::ignoreContentAdaptWithSize(bool ignore)
//{
//    if (_ignoreSize != ignore)
//    {
//        _formatTextDirty = true;
//        Widget::ignoreContentAdaptWithSize(ignore);
//    }
//}
//void XPRichText::formarRenderers()
//{
//    if (_ignoreSize)
//    {
//        float newContentSizeWidth = 0.0f;
//        float nextPosY = 0.0f;
//        for (auto& element: _elementRenders)
//        {
//            Vector<Node*>* row = element;
//            float nextPosX = 0.0f;
//            float maxY = 0.0f;
//            for (auto& iter : *row)
//            {
//                iter->setAnchorPoint(Vec2::ZERO);
//                iter->setPosition(nextPosX, nextPosY);
//                this->addProtectedChild(iter, 1);
//                Size iSize = iter->getContentSize();
//                newContentSizeWidth += iSize.width;
//                nextPosX += iSize.width;
//                maxY = MAX(maxY, iSize.height);
//            }
//            nextPosY -= maxY;
//        }
//        this->setContentSize(Size(newContentSizeWidth, -nextPosY));
//    }
//    else
//    {
//        float newContentSizeHeight = 0.0f;
//        float *maxHeights = new (std::nothrow) float[_elementRenders.size()];
//
//        for (size_t i=0, size = _elementRenders.size(); i<size; i++)
//        {
//            Vector<Node*>* row = (_elementRenders[i]);
//            float maxHeight = 0.0f;
//            for (auto& iter : *row)
//            {
//                maxHeight = MAX(iter->getContentSize().height, maxHeight);
//            }
//            maxHeights[i] = maxHeight;
//            newContentSizeHeight += maxHeights[i];
//        }
//
//        float nextPosY = _customSize.height;
//        for (size_t i=0, size = _elementRenders.size(); i<size; i++)
//        {
//            Vector<Node*>* row = (_elementRenders[i]);
//            float nextPosX = 0.0f;
//            //nextPosY -= (maxHeights[i] + _defaults.at(KEY_VERTICAL_SPACE).asFloat());
//            nextPosY -= (maxHeights[i] + 0);
//            for (auto& iter : *row)
//            {
//                iter->setAnchorPoint(Vec2::ZERO);
//                iter->setPosition(nextPosX, nextPosY);
//                this->addProtectedChild(iter, 1);
//                nextPosX += iter->getContentSize().width;
//            }
//        }
//        delete [] maxHeights;
//    }
//
//    for (auto& iter : _elementRenders)
//    {
//        iter->clear();
//        delete iter;
//    }
//    _elementRenders.clear();
//
//    if (_ignoreSize)
//    {
//        Size s = getVirtualRendererSize();
//        this->setContentSize(s);
//    }
//    else
//    {
//        this->setContentSize(_customSize);
//    }
//    updateContentSizeWithTextureSize(_contentSize);
//}
