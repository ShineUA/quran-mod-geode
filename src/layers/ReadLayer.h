#include <Geode/Bindings.hpp>
#include <string>

using namespace geode::prelude;

class ReadLayer : public geode::Popup<> {
    protected:
        MDTextArea* m_textArea;
        Scrollbar* m_scrollbar;
        CCLabelBMFont* m_pageText;
        int m_maxQuranPages = 241;
        int m_page = 1;
        virtual bool setup() override;
        virtual std::string readPage(int page);
        virtual void changePage(cocos2d::CCObject* sender);
    public:
        static ReadLayer* create();
};