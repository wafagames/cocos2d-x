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
    _fixedSize=fixedSize;
    _alignH=alignH;
    _alignV=alignV;
    _newLinePolicy=newLinePolicy;
    _debug=debug;
}

XPRichText::~XPRichText()
{
    _richElements.clear();
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
    {
        return true;
    }
    return false;
}

void XPRichText::initRenderer()
{
//    if(_debug){
//        _drawNode=DrawNode::create();
//    }
}


void XPRichText::insertElement(RichElement *element, int index)
{
    _richElements.insert(index, element);
    _formatTextDirty = true;
}


void XPRichText::pushBackElement(RichElement *element)
{
    _richElements.pushBack(element);
    _formatTextDirty = true;
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

void XPRichText::formatText()
{
    if (_formatTextDirty)
    {
        this->removeAllProtectedChildren();
        _elementRenders.clear();
        if (_ignoreSize)
        {
            addNewLine();
            for (ssize_t i=0, size = _richElements.size(); i<size; ++i)
            {
                RichElement* element = _richElements.at(i);
                Node* elementRenderer = nullptr;
                switch (element->_type)
                {
                    case RichElement::Type::TEXT:
                    {
                        RichElementText* elmtText = static_cast<RichElementText*>(element);
                        cocos2d::Label* label;
                        if (FileUtils::getInstance()->isFileExist(elmtText->_fontName))
                        {
                            label = cocos2d::Label::createWithTTF(elmtText->_text, elmtText->_fontName, elmtText->_fontSize);
                        }
                        else
                        {
                            label = cocos2d::Label::createWithSystemFont(elmtText->_text, elmtText->_fontName, elmtText->_fontSize);
                        }
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
                        elementRenderer = label;
                        break;
                    }
                    case RichElement::Type::IMAGE:
                    {
                        RichElementImage* elmtImage = static_cast<RichElementImage*>(element);
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
                        break;
                    }
                    default:
                        break;
                }

                if (elementRenderer)
                {
                    elementRenderer->setColor(element->_color);
                    elementRenderer->setOpacity(element->_opacity);
                    pushToContainer(elementRenderer);
                }
            }
        }
        else
        {
            addNewLine();
            for (ssize_t i=0, size = _richElements.size(); i<size; ++i)
            {
                RichElement* element = static_cast<RichElement*>(_richElements.at(i));
                switch (element->_type)
                {
                    case RichElement::Type::TEXT:
                    {
                        RichElementText* elmtText = static_cast<RichElementText*>(element);
                        handleTextRenderer(elmtText->_text, elmtText->_fontName, elmtText->_fontSize, elmtText->_color,
                                           elmtText->_opacity, elmtText->_flags, elmtText->_url,
                                           elmtText->_outlineColor, elmtText->_outlineSize,
                                           elmtText->_shadowColor, elmtText->_shadowOffset, elmtText->_shadowBlurRadius,
                                           elmtText->_glowColor);
                        break;
                    }
                    case RichElement::Type::IMAGE:
                    {
                        RichElementImage* elmtImage = static_cast<RichElementImage*>(element);
                        handleImageRenderer(elmtImage->_filePath, elmtImage->_color, elmtImage->_opacity, elmtImage->_width, elmtImage->_height, elmtImage->_url);
                        break;
                    }
                    case RichElement::Type::CUSTOM:
                    {
                        RichElementCustomNode* elmtCustom = static_cast<RichElementCustomNode*>(element);
                        handleCustomRenderer(elmtCustom->_customNode);
                        break;
                    }
                    case RichElement::Type::NEWLINE:
                    {
                        addNewLine();
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

void XPRichText::handleTextRenderer(const std::string& text, const std::string& fontName, float fontSize, const Color3B &color,
                                  GLubyte opacity, uint32_t flags, const std::string& url,
                                  const Color3B& outlineColor, int outlineSize ,
                                  const Color3B& shadowColor, const cocos2d::Size& shadowOffset, int shadowBlurRadius,
                                  const Color3B& glowColor)
{
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
                leftRenderer->setColor(color);
                leftRenderer->setOpacity(opacity);
                pushToContainer(leftRenderer);

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

        addNewLine();
        handleTextRenderer(cutWords, fontName, fontSize, color, opacity, flags, url,
                           outlineColor, outlineSize,
                           shadowColor, shadowOffset, shadowBlurRadius,
                           glowColor);
    }
    else
    {
        textRenderer->setColor(color);
        textRenderer->setOpacity(opacity);
        pushToContainer(textRenderer);
    }
}

void XPRichText::handleImageRenderer(const std::string& filePath, const Color3B &/*color*/, GLubyte /*opacity*/, int width, int height, const std::string& url)
{
    Sprite* imageRenderer = Sprite::create(filePath);
    if (imageRenderer)
    {
        auto currentSize = imageRenderer->getContentSize();
        if (width != -1)
            imageRenderer->setScaleX(width / currentSize.width);
        if (height != -1)
            imageRenderer->setScaleY(height / currentSize.height);
        imageRenderer->setContentSize(Size(currentSize.width * imageRenderer->getScaleX(),
                                           currentSize.height * imageRenderer->getScaleY()));

        handleCustomRenderer(imageRenderer);
//        imageRenderer->addComponent(ListenerComponent::create(imageRenderer,
//                                                              url,
//                                                              std::bind(&RichText::openUrl, this, std::placeholders::_1)));
    }
}

void XPRichText::handleCustomRenderer(cocos2d::Node *renderer)
{
    Size imgSize = renderer->getContentSize();
    _leftSpaceWidth -= imgSize.width;
    if (_leftSpaceWidth < 0.0f)
    {
        addNewLine();
        pushToContainer(renderer);
        _leftSpaceWidth -= imgSize.width;
    }
    else
    {
        pushToContainer(renderer);
    }
}

void XPRichText::addNewLine()
{
    _leftSpaceWidth = _customSize.width;
    _elementRenders.push_back(new Vector<Node*>());
}

void XPRichText::formarRenderers()
{
    if (_ignoreSize)
    {
        float newContentSizeWidth = 0.0f;
        float nextPosY = 0.0f;
        for (auto& element: _elementRenders)
        {
            Vector<Node*>* row = element;
            float nextPosX = 0.0f;
            float maxY = 0.0f;
            for (auto& iter : *row)
            {
                iter->setAnchorPoint(Vec2::ZERO);
                iter->setPosition(nextPosX, nextPosY);
                this->addProtectedChild(iter, 1);
                Size iSize = iter->getContentSize();
                newContentSizeWidth += iSize.width;
                nextPosX += iSize.width;
                maxY = MAX(maxY, iSize.height);
            }
            nextPosY -= maxY;
        }
        this->setContentSize(Size(newContentSizeWidth, -nextPosY));
    }
    else
    {
        float newContentSizeHeight = 0.0f;
        float *maxHeights = new (std::nothrow) float[_elementRenders.size()];

        for (size_t i=0, size = _elementRenders.size(); i<size; i++)
        {
            Vector<Node*>* row = (_elementRenders[i]);
            float maxHeight = 0.0f;
            for (auto& iter : *row)
            {
                maxHeight = MAX(iter->getContentSize().height, maxHeight);
            }
            maxHeights[i] = maxHeight;
            newContentSizeHeight += maxHeights[i];
        }

        float nextPosY = _customSize.height;
        for (size_t i=0, size = _elementRenders.size(); i<size; i++)
        {
            Vector<Node*>* row = (_elementRenders[i]);
            float nextPosX = 0.0f;
            //nextPosY -= (maxHeights[i] + _defaults.at(KEY_VERTICAL_SPACE).asFloat());
            nextPosY -= (maxHeights[i] + 0);
            for (auto& iter : *row)
            {
                iter->setAnchorPoint(Vec2::ZERO);
                iter->setPosition(nextPosX, nextPosY);
                this->addProtectedChild(iter, 1);
                nextPosX += iter->getContentSize().width;
            }
        }
        delete [] maxHeights;
    }

    for (auto& iter : _elementRenders)
    {
        iter->clear();
        delete iter;
    }
    _elementRenders.clear();

    if (_ignoreSize)
    {
        Size s = getVirtualRendererSize();
        this->setContentSize(s);
    }
    else
    {
        this->setContentSize(_customSize);
    }
    updateContentSizeWithTextureSize(_contentSize);
}

void XPRichText::adaptRenderers()
{
    this->formatText();
}

void XPRichText::pushToContainer(cocos2d::Node *renderer)
{
    if (_elementRenders.size() <= 0)
    {
        return;
    }
    _elementRenders[_elementRenders.size()-1]->pushBack(renderer);
}

//void XPRichText::setVerticalSpace(float space)
//{
//    _defaults[KEY_VERTICAL_SPACE] = space;
//}

void XPRichText::ignoreContentAdaptWithSize(bool ignore)
{
    if (_ignoreSize != ignore)
    {
        _formatTextDirty = true;
        Widget::ignoreContentAdaptWithSize(ignore);
    }
}

std::string XPRichText::getDescription() const
{
    return "XPRichText";
}

