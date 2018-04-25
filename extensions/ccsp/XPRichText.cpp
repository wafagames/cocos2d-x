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


//const std::string XPRichText::KEY_VERTICAL_SPACE("KEY_VERTICAL_SPACE");
//const std::string XPRichText::KEY_WRAP_MODE("KEY_WRAP_MODE");
//const std::string XPRichText::KEY_FONT_COLOR_STRING("KEY_FONT_COLOR_STRING");
//const std::string XPRichText::KEY_FONT_SIZE("KEY_FONT_SIZE");
//const std::string XPRichText::KEY_FONT_SMALL("KEY_FONT_SMALL");
//const std::string XPRichText::KEY_FONT_BIG("KEY_FONT_BIG");
//const std::string XPRichText::KEY_FONT_FACE("KEY_FONT_FACE");
//const std::string XPRichText::KEY_TEXT_BOLD("KEY_TEXT_BOLD");
//const std::string XPRichText::KEY_TEXT_ITALIC("KEY_TEXT_ITALIC");
//const std::string XPRichText::KEY_TEXT_LINE("KEY_TEXT_LINE");
//const std::string XPRichText::VALUE_TEXT_LINE_NONE("VALUE_TEXT_LINE_NONE");
//const std::string XPRichText::VALUE_TEXT_LINE_DEL("VALUE_TEXT_LINE_DEL");
//const std::string XPRichText::VALUE_TEXT_LINE_UNDER("VALUE_TEXT_LINE_UNDER");
//const std::string XPRichText::KEY_TEXT_STYLE("KEY_TEXT_STYLE");
//const std::string XPRichText::VALUE_TEXT_STYLE_NONE("VALUE_TEXT_STYLE_NONE");
//const std::string XPRichText::VALUE_TEXT_STYLE_OUTLINE("VALUE_TEXT_STYLE_OUTLINE");
//const std::string XPRichText::VALUE_TEXT_STYLE_SHADOW("VALUE_TEXT_STYLE_SHADOW");
//const std::string XPRichText::VALUE_TEXT_STYLE_GLOW("VALUE_TEXT_STYLE_GLOW");
//const std::string XPRichText::KEY_TEXT_OUTLINE_COLOR("KEY_TEXT_OUTLINE_COLOR");
//const std::string XPRichText::KEY_TEXT_OUTLINE_SIZE("KEY_TEXT_OUTLINE_SIZE");
//const std::string XPRichText::KEY_TEXT_SHADOW_COLOR("KEY_TEXT_SHADOW_COLOR");
//const std::string XPRichText::KEY_TEXT_SHADOW_OFFSET_WIDTH("KEY_TEXT_SHADOW_OFFSET_WIDTH");
//const std::string XPRichText::KEY_TEXT_SHADOW_OFFSET_HEIGHT("KEY_TEXT_SHADOW_OFFSET_HEIGHT");
//const std::string XPRichText::KEY_TEXT_SHADOW_BLUR_RADIUS("KEY_TEXT_SHADOW_BLUR_RADIUS");
//const std::string XPRichText::KEY_TEXT_GLOW_COLOR("KEY_TEXT_GLOW_COLOR");
//const std::string XPRichText::KEY_URL("KEY_URL");
//const std::string XPRichText::KEY_ANCHOR_FONT_COLOR_STRING("KEY_ANCHOR_FONT_COLOR_STRING");
//const std::string XPRichText::KEY_ANCHOR_TEXT_BOLD("KEY_ANCHOR_TEXT_BOLD");
//const std::string XPRichText::KEY_ANCHOR_TEXT_ITALIC("KEY_ANCHOR_TEXT_ITALIC");
//const std::string XPRichText::KEY_ANCHOR_TEXT_LINE("KEY_ANCHOR_TEXT_LINE");
//const std::string XPRichText::KEY_ANCHOR_TEXT_STYLE("KEY_ANCHOR_TEXT_STYLE");
//const std::string XPRichText::KEY_ANCHOR_TEXT_OUTLINE_COLOR("KEY_ANCHOR_TEXT_OUTLINE_COLOR");
//const std::string XPRichText::KEY_ANCHOR_TEXT_OUTLINE_SIZE("KEY_ANCHOR_TEXT_OUTLINE_SIZE");
//const std::string XPRichText::KEY_ANCHOR_TEXT_SHADOW_COLOR("KEY_ANCHOR_TEXT_SHADOW_COLOR");
//const std::string XPRichText::KEY_ANCHOR_TEXT_SHADOW_OFFSET_WIDTH("KEY_ANCHOR_TEXT_SHADOW_OFFSET_WIDTH");
//const std::string XPRichText::KEY_ANCHOR_TEXT_SHADOW_OFFSET_HEIGHT("KEY_ANCHOR_TEXT_SHADOW_OFFSET_HEIGHT");
//const std::string XPRichText::KEY_ANCHOR_TEXT_SHADOW_BLUR_RADIUS("KEY_ANCHOR_TEXT_SHADOW_BLUR_RADIUS");
//const std::string XPRichText::KEY_ANCHOR_TEXT_GLOW_COLOR("KEY_ANCHOR_TEXT_GLOW_COLOR");

XPRichText::XPRichText()
: _formatTextDirty(true)
, _leftSpaceWidth(0.0f)
{
//    _defaults[KEY_VERTICAL_SPACE] = 0.0f;
//    _defaults[KEY_WRAP_MODE] = static_cast<int>(WrapMode::WRAP_PER_WORD);
//    _defaults[KEY_FONT_COLOR_STRING] = "#ffffff";
//    _defaults[KEY_FONT_SIZE] = 12.0f;
//    _defaults[KEY_FONT_FACE] = "Verdana";
//    _defaults[KEY_ANCHOR_FONT_COLOR_STRING] = "#0000FF";
//    _defaults[KEY_ANCHOR_TEXT_BOLD] = false;
//    _defaults[KEY_ANCHOR_TEXT_ITALIC] = false;
//    _defaults[KEY_ANCHOR_TEXT_LINE] = VALUE_TEXT_LINE_NONE;
//    _defaults[KEY_ANCHOR_TEXT_STYLE] = VALUE_TEXT_STYLE_NONE;
}

XPRichText::~XPRichText()
{
    _richElements.clear();
}

XPRichText* XPRichText::create()
{
    XPRichText* widget = new (std::nothrow) XPRichText();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}

//XPRichText* XPRichText::createWithXML(const std::string& xml, const ValueMap& defaults, const OpenUrlHandler& handleOpenUrl)
//{
//    XPRichText* widget = new (std::nothrow) XPRichText();
//    if (widget && widget->initWithXML(xml, defaults, handleOpenUrl))
//    {
//        widget->autorelease();
//        return widget;
//    }
//    CC_SAFE_DELETE(widget);
//    return nullptr;
//}
//bool XPRichText::initWithXML(const std::string& origxml, const ValueMap& defaults, const OpenUrlHandler& handleOpenUrl)
//{
//    static std::function<std::string(XPRichText*)> startTagFont = [](XPRichText* richText) {
//        std::string fontFace = richText->getFontFace();
//        std::stringstream ss;
//        ss << richText->getFontSize();
//        std::string fontSize = ss.str();
//        std::string fontColor = richText->getFontColor();
//        return "<font face=\"" + fontFace + "\" size=\"" + fontSize + "\" color=\"" + fontColor + "\">";
//    };
//    if (Widget::init())
//    {
//        setDefaults(defaults);
//        setOpenUrlHandler(handleOpenUrl);
//
//        // solves to issues:
//        //  - creates defaults values
//        //  - makes sure that the xml well formed and starts with an element
//        std::string xml = startTagFont(this);
//        xml += origxml;
//        xml += "</font>";
//
//        MyXMLVisitor visitor(this);
//        SAXParser parser;
//        parser.setDelegator(&visitor);
//        return parser.parseIntrusive(&xml.front(), xml.length());
//    }
//    return false;
//}

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

//void XPRichText::removeElement(int index)
//{
//    _richElements.erase(index);
//    _formatTextDirty = true;
//}
//
//void XPRichText::removeElement(RichElement *element)
//{
//    _richElements.eraseObject(element);
//    _formatTextDirty = true;
//}
//
//XPRichText::WrapMode XPRichText::getWrapMode() const
//{
//    return static_cast<XPRichText::WrapMode>(_defaults.at(KEY_WRAP_MODE).asInt());
//}
//
//void XPRichText::setWrapMode(XPRichText::WrapMode wrapMode)
//{
//    if (static_cast<XPRichText::WrapMode>(_defaults.at(KEY_WRAP_MODE).asInt()) != wrapMode)
//    {
//        _defaults[KEY_WRAP_MODE] = static_cast<int>(wrapMode);
//        _formatTextDirty = true;
//    }
//}
//
//void XPRichText::setFontColor(const std::string& color)
//{
//    _defaults[KEY_FONT_COLOR_STRING] = color;
//}
//
//std::string XPRichText::getFontColor()
//{
//    return _defaults.at(KEY_FONT_COLOR_STRING).asString();
//}
//
//cocos2d::Color3B XPRichText::getFontColor3B()
//{
//    return color3BWithString(getFontColor());
//}
//
//void XPRichText::setFontSize(float size)
//{
//    _defaults[KEY_FONT_SIZE] = size;
//}
//
//float XPRichText::getFontSize()
//{
//    return _defaults.at(KEY_FONT_SIZE).asFloat();
//}
//
//void XPRichText::setFontFace(const std::string& face)
//{
//    _defaults[KEY_FONT_FACE] = face;
//}
//
//std::string XPRichText::getFontFace()
//{
//    return _defaults.at(KEY_FONT_FACE).asString();
//}
//
//void XPRichText::setAnchorFontColor(const std::string& color)
//{
//    _defaults[KEY_ANCHOR_FONT_COLOR_STRING] = color;
//}
//
//std::string XPRichText::getAnchorFontColor()
//{
//    return _defaults.at(KEY_ANCHOR_FONT_COLOR_STRING).asString();
//}
//
//cocos2d::Color3B XPRichText::getAnchorFontColor3B()
//{
//    return color3BWithString(getAnchorFontColor());
//}
//
//void XPRichText::setAnchorTextBold(bool enable)
//{
//    _defaults[KEY_ANCHOR_TEXT_BOLD] = enable;
//}
//
//bool XPRichText::isAnchorTextBoldEnabled()
//{
//    return _defaults[KEY_ANCHOR_TEXT_BOLD].asBool();
//}
//
//void XPRichText::setAnchorTextItalic(bool enable)
//{
//    _defaults[KEY_ANCHOR_TEXT_ITALIC] = enable;
//}
//
//bool XPRichText::isAnchorTextItalicEnabled()
//{
//    return _defaults[KEY_ANCHOR_TEXT_ITALIC].asBool();
//}
//
//void XPRichText::setAnchorTextDel(bool enable)
//{
//    if (enable)
//        _defaults[KEY_ANCHOR_TEXT_LINE] = VALUE_TEXT_LINE_DEL;
//    else if (_defaults[KEY_ANCHOR_TEXT_LINE].asString() == VALUE_TEXT_LINE_DEL)
//        _defaults[KEY_ANCHOR_TEXT_LINE] = VALUE_TEXT_LINE_NONE;
//}
//
//bool XPRichText::isAnchorTextDelEnabled()
//{
//    return (_defaults[KEY_ANCHOR_TEXT_LINE].asString() == VALUE_TEXT_LINE_DEL);
//}
//
//void XPRichText::setAnchorTextUnderline(bool enable)
//{
//    if (enable)
//        _defaults[KEY_ANCHOR_TEXT_LINE] = VALUE_TEXT_LINE_UNDER;
//    else if (_defaults[KEY_ANCHOR_TEXT_LINE].asString() == VALUE_TEXT_LINE_UNDER)
//        _defaults[KEY_ANCHOR_TEXT_LINE] = VALUE_TEXT_LINE_NONE;
//}
//
//bool XPRichText::isAnchorTextUnderlineEnabled()
//{
//    return (_defaults[KEY_ANCHOR_TEXT_LINE].asString() == VALUE_TEXT_LINE_UNDER);
//}
//
//void XPRichText::setAnchorTextOutline(bool enable, const Color3B& outlineColor, int outlineSize)
//{
//    if (enable)
//        _defaults[KEY_ANCHOR_TEXT_STYLE] = VALUE_TEXT_STYLE_OUTLINE;
//    else if (_defaults[KEY_ANCHOR_TEXT_STYLE].asString() == VALUE_TEXT_STYLE_OUTLINE)
//        _defaults[KEY_ANCHOR_TEXT_STYLE] = VALUE_TEXT_STYLE_NONE;
//    _defaults[KEY_ANCHOR_TEXT_OUTLINE_COLOR] = stringWithColor3B(outlineColor);
//    _defaults[KEY_ANCHOR_TEXT_OUTLINE_SIZE] = outlineSize;
//}
//
//bool XPRichText::isAnchorTextOutlineEnabled()
//{
//    return (_defaults[KEY_ANCHOR_TEXT_STYLE].asString() == VALUE_TEXT_STYLE_OUTLINE);
//}
//
//Color3B XPRichText::getAnchorTextOutlineColor3B()
//{
//    if (_defaults.find(KEY_ANCHOR_TEXT_OUTLINE_COLOR) != _defaults.end()) {
//        return color3BWithString(_defaults.at(KEY_ANCHOR_TEXT_OUTLINE_COLOR).asString());
//    }
//    return Color3B();
//}
//
//int XPRichText::getAnchorTextOutlineSize()
//{
//    if (_defaults.find(KEY_ANCHOR_TEXT_OUTLINE_SIZE) != _defaults.end()) {
//        return _defaults.at(KEY_ANCHOR_TEXT_OUTLINE_SIZE).asInt();
//    }
//    return -1;
//}
//
//void XPRichText::setAnchorTextShadow(bool enable, const Color3B& shadowColor, const Size& offset, int blurRadius)
//{
//    if (enable)
//        _defaults[KEY_ANCHOR_TEXT_STYLE] = VALUE_TEXT_STYLE_SHADOW;
//    else if (_defaults[KEY_ANCHOR_TEXT_STYLE].asString() == VALUE_TEXT_STYLE_SHADOW)
//        _defaults[KEY_ANCHOR_TEXT_STYLE] = VALUE_TEXT_STYLE_NONE;
//    _defaults[KEY_ANCHOR_TEXT_SHADOW_COLOR] = stringWithColor3B(shadowColor);
//    _defaults[KEY_ANCHOR_TEXT_SHADOW_OFFSET_WIDTH] = offset.width;
//    _defaults[KEY_ANCHOR_TEXT_SHADOW_OFFSET_HEIGHT] = offset.height;
//    _defaults[KEY_ANCHOR_TEXT_SHADOW_BLUR_RADIUS] = blurRadius;
//}
//
//bool XPRichText::isAnchorTextShadowEnabled()
//{
//    return (_defaults[KEY_ANCHOR_TEXT_STYLE].asString() == VALUE_TEXT_STYLE_SHADOW);
//}
//
//Color3B XPRichText::getAnchorTextShadowColor3B()
//{
//    if (_defaults.find(KEY_ANCHOR_TEXT_SHADOW_COLOR) != _defaults.end()) {
//        return color3BWithString(_defaults.at(KEY_ANCHOR_TEXT_SHADOW_COLOR).asString());
//    }
//    return Color3B();
//}
//
//Size XPRichText::getAnchorTextShadowOffset()
//{
//    float width = 2.0f;
//    float height = -2.0f;
//    if (_defaults.find(KEY_ANCHOR_TEXT_SHADOW_OFFSET_WIDTH) != _defaults.end()) {
//        width = _defaults.at(KEY_ANCHOR_TEXT_SHADOW_OFFSET_WIDTH).asFloat();
//    }
//    if (_defaults.find(KEY_ANCHOR_TEXT_SHADOW_OFFSET_HEIGHT) != _defaults.end()) {
//        height = _defaults.at(KEY_ANCHOR_TEXT_SHADOW_OFFSET_HEIGHT).asFloat();
//    }
//    return Size(width, height);
//}
//
//int XPRichText::getAnchorTextShadowBlurRadius()
//{
//    if (_defaults.find(KEY_ANCHOR_TEXT_SHADOW_BLUR_RADIUS) != _defaults.end()) {
//        return _defaults.at(KEY_ANCHOR_TEXT_SHADOW_BLUR_RADIUS).asInt();
//    }
//    return 0;
//}
//
//void XPRichText::setAnchorTextGlow(bool enable, const Color3B& glowColor)
//{
//    if (enable)
//        _defaults[KEY_ANCHOR_TEXT_STYLE] = VALUE_TEXT_STYLE_GLOW;
//    else if (_defaults[KEY_ANCHOR_TEXT_STYLE].asString() == VALUE_TEXT_STYLE_GLOW)
//        _defaults[KEY_ANCHOR_TEXT_STYLE] = VALUE_TEXT_STYLE_NONE;
//    _defaults[KEY_ANCHOR_TEXT_GLOW_COLOR] = stringWithColor3B(glowColor);
//}
//
//bool XPRichText::isAnchorTextGlowEnabled()
//{
//    return (_defaults[KEY_ANCHOR_TEXT_STYLE].asString() == VALUE_TEXT_STYLE_GLOW);
//}
//
//Color3B XPRichText::getAnchorTextGlowColor3B()
//{
//    if (_defaults.find(KEY_ANCHOR_TEXT_GLOW_COLOR) != _defaults.end()) {
//        return color3BWithString(_defaults.at(KEY_ANCHOR_TEXT_GLOW_COLOR).asString());
//    }
//    return Color3B();
//}
//
//void XPRichText::setDefaults(const ValueMap& defaults)
//{
//    if (defaults.find(KEY_VERTICAL_SPACE) != defaults.end()) {
//        _defaults[KEY_VERTICAL_SPACE] = defaults.at(KEY_VERTICAL_SPACE).asFloat();
//    }
//    if (defaults.find(KEY_WRAP_MODE) != defaults.end()) {
//        _defaults[KEY_WRAP_MODE] = defaults.at(KEY_WRAP_MODE).asInt();
//    }
//    if (defaults.find(KEY_FONT_COLOR_STRING) != defaults.end()) {
//        _defaults[KEY_FONT_COLOR_STRING] = defaults.at(KEY_FONT_COLOR_STRING).asString();
//    }
//    if (defaults.find(KEY_FONT_SIZE) != defaults.end()) {
//        _defaults[KEY_FONT_SIZE] = defaults.at(KEY_FONT_SIZE).asFloat();
//    }
//    if (defaults.find(KEY_FONT_FACE) != defaults.end()) {
//        _defaults[KEY_FONT_FACE] = defaults.at(KEY_FONT_FACE).asString();
//    }
//    if (defaults.find(KEY_ANCHOR_FONT_COLOR_STRING) != defaults.end()) {
//        _defaults[KEY_ANCHOR_FONT_COLOR_STRING] = defaults.at(KEY_ANCHOR_FONT_COLOR_STRING).asString();
//    }
//    if (defaults.find(KEY_ANCHOR_TEXT_BOLD) != defaults.end()) {
//        _defaults[KEY_ANCHOR_TEXT_BOLD] = defaults.at(KEY_ANCHOR_TEXT_BOLD).asBool();
//    }
//    if (defaults.find(KEY_ANCHOR_TEXT_ITALIC) != defaults.end()) {
//        _defaults[KEY_ANCHOR_TEXT_ITALIC] = defaults.at(KEY_ANCHOR_TEXT_ITALIC).asBool();
//    }
//    if (defaults.find(KEY_ANCHOR_TEXT_LINE) != defaults.end()) {
//        _defaults[KEY_ANCHOR_TEXT_LINE] = defaults.at(KEY_ANCHOR_TEXT_LINE).asString();
//    }
//    if (defaults.find(KEY_ANCHOR_TEXT_STYLE) != defaults.end()) {
//        _defaults[KEY_ANCHOR_TEXT_STYLE] = defaults.at(KEY_ANCHOR_TEXT_STYLE).asString();
//    }
//    if (defaults.find(KEY_ANCHOR_TEXT_OUTLINE_COLOR) != defaults.end()) {
//        _defaults[KEY_ANCHOR_TEXT_OUTLINE_COLOR] = defaults.at(KEY_ANCHOR_TEXT_OUTLINE_COLOR).asString();
//    }
//    if (defaults.find(KEY_ANCHOR_TEXT_OUTLINE_SIZE) != defaults.end()) {
//        _defaults[KEY_ANCHOR_TEXT_OUTLINE_SIZE] = defaults.at(KEY_ANCHOR_TEXT_OUTLINE_SIZE).asInt();
//    }
//    if (defaults.find(KEY_ANCHOR_TEXT_SHADOW_COLOR) != defaults.end()) {
//        _defaults[KEY_ANCHOR_TEXT_SHADOW_COLOR] = defaults.at(KEY_ANCHOR_TEXT_SHADOW_COLOR).asString();
//    }
//    if (defaults.find(KEY_ANCHOR_TEXT_SHADOW_OFFSET_WIDTH) != defaults.end()) {
//        _defaults[KEY_ANCHOR_TEXT_SHADOW_OFFSET_WIDTH] = defaults.at(KEY_ANCHOR_TEXT_SHADOW_OFFSET_WIDTH).asFloat();
//    }
//    if (defaults.find(KEY_ANCHOR_TEXT_SHADOW_OFFSET_HEIGHT) != defaults.end()) {
//        _defaults[KEY_ANCHOR_TEXT_SHADOW_OFFSET_HEIGHT] = defaults.at(KEY_ANCHOR_TEXT_SHADOW_OFFSET_HEIGHT).asFloat();
//    }
//    if (defaults.find(KEY_ANCHOR_TEXT_SHADOW_BLUR_RADIUS) != defaults.end()) {
//        _defaults[KEY_ANCHOR_TEXT_SHADOW_BLUR_RADIUS] = defaults.at(KEY_ANCHOR_TEXT_SHADOW_BLUR_RADIUS).asInt();
//    }
//    if (defaults.find(KEY_ANCHOR_TEXT_GLOW_COLOR) != defaults.end()) {
//        _defaults[KEY_ANCHOR_TEXT_GLOW_COLOR] = defaults.at(KEY_ANCHOR_TEXT_GLOW_COLOR).asString();
//    }
//}
//
//ValueMap XPRichText::getDefaults() const
//{
//    ValueMap defaults;
//    return defaults;
//}
//
//cocos2d::Color3B XPRichText::color3BWithString(const std::string& color)
//{
//    if (color.length() == 4) {
//        int r, g, b;
//        sscanf(color.c_str(), "%*c%1x%1x%1x", &r, &g, &b);
//        r += r * 16;
//        g += g * 16;
//        b += b * 16;
//        return Color3B(r, g, b);
//    }
//    else if (color.length() == 7) {
//        int r, g, b;
//        sscanf(color.c_str(), "%*c%2x%2x%2x", &r, &g, &b);
//        return Color3B(r, g, b);
//    }
//    else if (color.length() == 9) {
//        int r, g, b, a;
//        sscanf(color.c_str(), "%*c%2x%2x%2x%2x", &r, &g, &b, &a);
//        return Color3B(r, g, b);
//    }
//    return Color3B::WHITE;
//}
//
//std::string XPRichText::stringWithColor3B(const cocos2d::Color3B& color3b)
//{
//    int r = color3b.r;
//    int g = color3b.g;
//    int b = color3b.b;
//    char buf[8];
//    snprintf(buf, sizeof(buf), "#%02x%02x%02x", r, g, b);
//    return std::string(buf, 7);
//}
//
//std::string XPRichText::stringWithColor4B(const cocos2d::Color4B& color4b)
//{
//    int r = color4b.r;
//    int g = color4b.g;
//    int b = color4b.b;
//    int a = color4b.a;
//    char buf[10];
//    snprintf(buf, sizeof(buf), "#%02x%02x%02x%02x", r, g, b, a);
//    return std::string(buf, 9);
//}
//
////void XPRichText::setTagDescription(const std::string& tag, bool isFontElement, VisitEnterHandler handleVisitEnter)
////{
////    MyXMLVisitor::setTagDescription(tag, isFontElement, handleVisitEnter);
////}
////
////void XPRichText::removeTagDescription(const std::string& tag)
////{
////    MyXMLVisitor::removeTagDescription(tag);
////}

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
//
//
//int XPRichText::findSplitPositionForChar(cocos2d::Label* label, const std::string& text)
//{
//    float textRendererWidth = label->getContentSize().width;
//
//    float overstepPercent = (-_leftSpaceWidth) / textRendererWidth;
//    std::string curText = text;
//    size_t stringLength = StringUtils::getCharacterCountInUTF8String(text);
//
//    // rough estimate
//    int leftLength = stringLength * (1.0f - overstepPercent);
//
//    // The adjustment of the new line position
//    auto originalLeftSpaceWidth = _leftSpaceWidth + textRendererWidth;
//    auto leftStr = Helper::getSubStringOfUTF8String(curText, 0, leftLength);
//    label->setString(leftStr);
//    auto leftWidth = label->getContentSize().width;
//    if (originalLeftSpaceWidth < leftWidth) {
//        // Have protruding
//        for (;;) {
//            leftLength--;
//            leftStr = Helper::getSubStringOfUTF8String(curText, 0, leftLength);
//            label->setString(leftStr);
//            leftWidth = label->getContentSize().width;
//            if (leftWidth <= originalLeftSpaceWidth) {
//                break;
//            }
//            else if (leftLength <= 0) {
//                break;
//            }
//        }
//    }
//    else if (leftWidth < originalLeftSpaceWidth) {
//        // A wide margin
//        for (;;) {
//            leftLength++;
//            leftStr = Helper::getSubStringOfUTF8String(curText, 0, leftLength);
//            label->setString(leftStr);
//            leftWidth = label->getContentSize().width;
//            if (originalLeftSpaceWidth < leftWidth) {
//                leftLength--;
//                break;
//            }
//            else if (static_cast<int>(stringLength) <= leftLength) {
//                break;
//            }
//        }
//    }
//
//    if (leftLength < 0)
//        leftLength = (int)text.size()-1;
//    return leftLength;
//}
//
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

