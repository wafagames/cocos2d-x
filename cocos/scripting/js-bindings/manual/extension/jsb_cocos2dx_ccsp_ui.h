//
//  jsb_cocos2dx_ccsp_ui.h
//  cocos2d_js_bindings
//
//  Created by joe on 2018/4/25.
//

#include "base/ccConfig.h"

#include "jsapi.h"
#include "jsfriendapi.h"

extern JSClass  *jsb_XPRichText_class;
extern JSObject *jsb_XPRichText_prototype;


void js_register_XPRichText(JSContext *cx, JS::HandleObject global);

bool js_XPRichText_create(JSContext *cx, uint32_t argc, jsval *vp);
bool js_XPRichText_RichText(JSContext *cx, uint32_t argc, jsval *vp);
bool js_XPRichText_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_XPRichText_finalize(JSContext *cx, JSObject *obj);
bool js_XPRichText_pushBackElement(JSContext *cx, uint32_t argc, jsval *vp);

bool js_XPRichText_getRenderByID(JSContext *cx, uint32_t argc, jsval *vp);
bool js_XPRichText_addClickEventForRenderer(JSContext *cx, uint32_t argc, jsval *vp);
bool js_XPRichText_setRenderString(JSContext *cx, uint32_t argc, jsval *vp);
bool js_XPRichText_setRenderTexture(JSContext *cx, uint32_t argc, jsval *vp);
bool js_XPRichText_setOnRenderEnd(JSContext *cx, uint32_t argc, jsval *vp);
//void register_all_cocos2dx_ui(JSContext* cx, JS::HandleObject obj);
//bool js_cocos2dx_ui_RichText_formatText(JSContext *cx, uint32_t argc, jsval *vp);
//bool js_cocos2dx_ui_RichText_openUrl(JSContext *cx, uint32_t argc, jsval *vp);
//bool js_cocos2dx_ui_RichText_insertElement(JSContext *cx, uint32_t argc, jsval *vp);
//bool js_cocos2dx_ui_RichText_getFontSize(JSContext *cx, uint32_t argc, jsval *vp);
//bool js_cocos2dx_ui_RichText_setAnchorTextOutline(JSContext *cx, uint32_t argc, jsval *vp);
//bool js_cocos2dx_ui_RichText_setAnchorTextBold(JSContext *cx, uint32_t argc, jsval *vp);
//bool js_cocos2dx_ui_RichText_getAnchorFontColor(JSContext *cx, uint32_t argc, jsval *vp);
//bool js_cocos2dx_ui_RichText_getAnchorTextShadowBlurRadius(JSContext *cx, uint32_t argc, jsval *vp);
//bool js_cocos2dx_ui_RichText_setAnchorTextShadow(JSContext *cx, uint32_t argc, jsval *vp);
//bool js_cocos2dx_ui_RichText_isAnchorTextItalicEnabled(JSContext *cx, uint32_t argc, jsval *vp);
//bool js_cocos2dx_ui_RichText_setAnchorFontColor(JSContext *cx, uint32_t argc, jsval *vp);
//bool js_cocos2dx_ui_RichText_setFontFace(JSContext *cx, uint32_t argc, jsval *vp);
//bool js_cocos2dx_ui_RichText_setAnchorTextGlow(JSContext *cx, uint32_t argc, jsval *vp);
//bool js_cocos2dx_ui_RichText_setAnchorTextDel(JSContext *cx, uint32_t argc, jsval *vp);
//bool js_cocos2dx_ui_RichText_getAnchorTextOutlineColor3B(JSContext *cx, uint32_t argc, jsval *vp);
//bool js_cocos2dx_ui_RichText_stringWithColor4B(JSContext *cx, uint32_t argc, jsval *vp);
//bool js_cocos2dx_ui_RichText_initWithXML(JSContext *cx, uint32_t argc, jsval *vp);
//bool js_cocos2dx_ui_RichText_getAnchorFontColor3B(JSContext *cx, uint32_t argc, jsval *vp);
//bool js_cocos2dx_ui_RichText_getAnchorTextGlowColor3B(JSContext *cx, uint32_t argc, jsval *vp);
//bool js_cocos2dx_ui_RichText_getFontFace(JSContext *cx, uint32_t argc, jsval *vp);
//bool js_cocos2dx_ui_RichText_setFontColor(JSContext *cx, uint32_t argc, jsval *vp);
//bool js_cocos2dx_ui_RichText_isAnchorTextGlowEnabled(JSContext *cx, uint32_t argc, jsval *vp);
//bool js_cocos2dx_ui_RichText_getDefaults(JSContext *cx, uint32_t argc, jsval *vp);
//bool js_cocos2dx_ui_RichText_isAnchorTextUnderlineEnabled(JSContext *cx, uint32_t argc, jsval *vp);
//bool js_cocos2dx_ui_RichText_getFontColor(JSContext *cx, uint32_t argc, jsval *vp);
//bool js_cocos2dx_ui_RichText_isAnchorTextShadowEnabled(JSContext *cx, uint32_t argc, jsval *vp);
//bool js_cocos2dx_ui_RichText_getAnchorTextOutlineSize(JSContext *cx, uint32_t argc, jsval *vp);
//bool js_cocos2dx_ui_RichText_setVerticalSpace(JSContext *cx, uint32_t argc, jsval *vp);
//bool js_cocos2dx_ui_RichText_isAnchorTextDelEnabled(JSContext *cx, uint32_t argc, jsval *vp);
//bool js_cocos2dx_ui_RichText_setDefaults(JSContext *cx, uint32_t argc, jsval *vp);
//bool js_cocos2dx_ui_RichText_setWrapMode(JSContext *cx, uint32_t argc, jsval *vp);
//bool js_cocos2dx_ui_RichText_setFontSize(JSContext *cx, uint32_t argc, jsval *vp);
//bool js_cocos2dx_ui_RichText_removeElement(JSContext *cx, uint32_t argc, jsval *vp);
//bool js_cocos2dx_ui_RichText_setAnchorTextItalic(JSContext *cx, uint32_t argc, jsval *vp);
//bool js_cocos2dx_ui_RichText_getAnchorTextShadowOffset(JSContext *cx, uint32_t argc, jsval *vp);
//bool js_cocos2dx_ui_RichText_isAnchorTextBoldEnabled(JSContext *cx, uint32_t argc, jsval *vp);
//bool js_cocos2dx_ui_RichText_getAnchorTextShadowColor3B(JSContext *cx, uint32_t argc, jsval *vp);
//bool js_cocos2dx_ui_RichText_stringWithColor3B(JSContext *cx, uint32_t argc, jsval *vp);
//bool js_cocos2dx_ui_RichText_isAnchorTextOutlineEnabled(JSContext *cx, uint32_t argc, jsval *vp);
//bool js_cocos2dx_ui_RichText_getFontColor3B(JSContext *cx, uint32_t argc, jsval *vp);
//bool js_cocos2dx_ui_RichText_getWrapMode(JSContext *cx, uint32_t argc, jsval *vp);
//bool js_cocos2dx_ui_RichText_setAnchorTextUnderline(JSContext *cx, uint32_t argc, jsval *vp);
//bool js_cocos2dx_ui_RichText_color3BWithString(JSContext *cx, uint32_t argc, jsval *vp);
//bool js_cocos2dx_ui_RichText_createWithXML(JSContext *cx, uint32_t argc, jsval *vp);

