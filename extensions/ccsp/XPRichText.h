//
//  XPRichText.h
//  cocos2d_libs
//
//  Created by Joe on 2018/4/24.
//

#ifndef XPRichText_h
#define XPRichText_h

#include <stdio.h>
#include <string>

#include "ui/UIWidget.h"
#include "ui/GUIExport.h"
#include "base/CCValue.h"
#include "ui/UIRichText.h"
#include "cocos/2d/CCDrawNode.h"


class Label;
using namespace cocos2d;
using namespace cocos2d::ui;

namespace ccsp {
   

    /**
     *@brief A container for displaying various RichElements.
     * We could use it to display texts with images easily.
     */
    class CC_GUI_DLL XPRichText : public Widget
    {
    public:
        
//        enum WrapMode {
//            WRAP_PER_WORD,
//            WRAP_PER_CHAR
//        };
        
        /**
         * @brief call to open a resource specified by a URL
         * @param url a URL
         */
        typedef std::function<void(const std::string& url)> OpenUrlHandler;
        
        /**
         * @brief called on the specified tag
         * @param tagAttrValueMap the attributes of a tag
         * @result text attributes and RichElement
         */
        typedef std::function<std::pair<ValueMap, RichElement*>(const ValueMap& tagAttrValueMap)> VisitEnterHandler;
        
        /**
         * @brief Default constructor.
         * @js ctor
         * @lua new
         */
        XPRichText(float linneInner,Size fixedSize,TextHAlignment alignH,TextVAlignment alignV,int newLinePolicy,bool debug);
        
        /**
         * @brief Default destructor.
         * @js NA
         * @lua NA
         */
        virtual ~XPRichText();
        
        /**
         * @brief Create a empty XPRichText.
         *
         * @return XPRichText instance.
         */
        static XPRichText* create(float linneInner,Size fixedSize,TextHAlignment alignH,TextVAlignment alignV,int newLinePolicy,bool debug);
        //void insertElement(RichElement* element, int index);
        void pushBackElement(RichElement* element);

        void formatText();
        //override functions.
        //virtual void ignoreContentAdaptWithSize(bool ignore) override;
        virtual std::string getDescription() const override;

    

        void openUrl(const std::string& url);

        /**
         * @brief Asks the callback to open a resource specified by a URL.
         * @discussion If you set up your own URL in the anchor tag, it is used to intercept the URL open.
         * @param handleOpenUrl the callback
         */
        void setOpenUrlHandler(const OpenUrlHandler& handleOpenUrl);

        Node* getRenderByID(int);
        void addClickEventForRenderer(int i,std::function<void (Node*,Point)> cb);
        void setRenderString(int,std::string);
        void setRenderTexture(int,std::string);
        
    CC_CONSTRUCTOR_ACCESS:
        virtual bool init() override;
   
    protected:
        virtual void adaptRenderers() override;
        virtual void initRenderer() override;
        void pushToContainer(int index,Node* renderer);
        int handleTextRenderer(int index,const std::string& text, const std::string& fontName, float fontSize, const Color3B& color,
                                GLubyte opacity, uint32_t flags, const std::string& url="",
                                const Color3B& outlineColor = Color3B::WHITE, int outlineSize = -1,
                                const Color3B& shadowColor = Color3B::BLACK, const cocos2d::Size& shadowOffset = Size(2.0, -2.0), int shadowBlurRadius = 0,
                                const Color3B& glowColor = Color3B::WHITE);
        int handleImageRenderer(int index,const std::string& filePath, const Color3B& color, GLubyte opacity, int width, int height, const std::string& url);
        int handleCustomRenderer(int index,Node* renderer);
        void formarRenderers();
        void addNewLine();
        int findSplitPositionForWord(cocos2d::Label* label, const std::string& text);
        
        float _findMaxHeightInAllRenders();
        float _getLineHeight(Vector<Node*>* arr);
         float _getLineWidth(Vector<Node*>* arr);
        float _findMaxLineWidth();
        float _formatOneLine(Vector<Node*>* arr,TextHAlignment,TextVAlignment,float offsetY);
        void _adjustPositionY(float);
        void _addAllRenders();
        
        Node* _getHighestRenderInLine(Vector<Node*>* arr);
        void _debugDrawOneLine(Vector<Node*>* arr,float offsetX,float offsetY);
        void _debugDrawAllLines();
        void _updateClickArea();
        void _onClick();
        void _initClick();
        
        
        bool _formatTextDirty;
        Vector<RichElement*> _richElements;
        std::vector<Vector<Node*>*> _elementRenders;
        float _leftSpaceWidth;
        
        ValueMap _defaults;             /*!< default values */
        OpenUrlHandler _handleOpenUrl;  /*!< the callback for open URL */
        
        float _lineInner=0;
        float _fixWidth=0;
         float _fixHeight=0;
        bool _clickEnabled=false;
        
        float _maxLineWidth=0;
       
        TextHAlignment _alignH;
        TextVAlignment _alignV;
        int _newLinePolicy=0;
        bool _debug=false;
        DrawNode* _drawNode;
    };
    
}
#endif /* XPRichText_h */
