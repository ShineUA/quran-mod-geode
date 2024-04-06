#include "ReadLayer.h"
#include <fmt/core.h>

ReadLayer* ReadLayer::create() {
    ReadLayer* ret = new ReadLayer();
    if (ret && ret->initAnchored(435.f, 270.f)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool ReadLayer::setup() {
    const CCPoint center = this->m_bgSprite->getContentSize() / 2;
    this->setTitle("The Holy Quran (Koran)");

    this->m_pageText = CCLabelBMFont::create(fmt::format("{} page of {} pages", this->m_page, this->m_maxQuranPages).c_str(), "goldFont.fnt");
    this->m_pageText->setAnchorPoint({1, 1});
    this->m_pageText->setScale(0.526);
    this->m_pageText->setPosition({CCDirector::sharedDirector()->getWinSize().width - 71, CCDirector::sharedDirector()->getWinSize().height - 28});
#ifdef GEODE_IS_ANDROID
    this->m_pageText->setPosition({CCDirector::sharedDirector()->getWinSize().width - 151, CCDirector::sharedDirector()->getWinSize().height - 28});
#endif

    auto leftArrow_spr = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
    leftArrow_spr->setScale(0.8);
    auto leftArrow = CCMenuItemSpriteExtra::create(
        leftArrow_spr,
        this,
        menu_selector(ReadLayer::changePage)
    );
    leftArrow->setID("left");
    leftArrow->setPosition({center.x - 238, center.y - 10});

    auto rightArrow_spr = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
    rightArrow_spr->setScale(0.8);
    rightArrow_spr->setFlipX(true);
    auto rightArrow = CCMenuItemSpriteExtra::create(
        rightArrow_spr,
        this,
        menu_selector(ReadLayer::changePage)
    );
    rightArrow->setID("right");
    rightArrow->setPosition({center.x + 238, center.y - 10});

    this->m_textArea = MDTextArea::create(this->readPage(1).c_str(), {375, 205});
    this->m_textArea->setPosition({center.x - 7, center.y - 10});
    this->m_scrollbar = Scrollbar::create(this->m_textArea->getScrollLayer());
    this->m_scrollbar->setPosition({center.x + 200, center.y - 10});

    this->m_mainLayer->addChild(this->m_textArea);
    this->m_mainLayer->addChild(this->m_scrollbar);
    this->m_mainLayer->addChild(this->m_pageText);
    this->m_buttonMenu->addChild(leftArrow);
    this->m_buttonMenu->addChild(rightArrow);
    return true;
}

std::string ReadLayer::readPage(int page) {
    unsigned long size;
    std::stringstream ss;
    auto text = CCFileUtils::sharedFileUtils()->getFileData(fmt::format("shineua.quran/en-{}.txt", page).c_str(), "r", &size);

    for(unsigned long i = 0; i < size; i++) {
        ss << text[i];
    }

    return ss.str();
}

void ReadLayer::changePage(CCObject* sender) {
    if(static_cast<CCMenuItemSpriteExtra*>(sender)->getID() == "left") {
        if(this->m_page != 1) {
            this->m_page--;
            this->m_pageText->setString(fmt::format("{} page of {} pages", this->m_page, this->m_maxQuranPages).c_str());
            this->m_textArea->setString(this->readPage(this->m_page).c_str());
        } else {
            this->m_page = this->m_maxQuranPages;
            this->m_pageText->setString(fmt::format("{} page of {} pages", this->m_page, this->m_maxQuranPages).c_str());
            this->m_textArea->setString(this->readPage(this->m_page).c_str());
        }
    } else if(static_cast<CCMenuItemSpriteExtra*>(sender)->getID() == "right") {
        if(this->m_page != this->m_maxQuranPages) {
            this->m_page++;
            this->m_pageText->setString(fmt::format("{} page of {} pages", this->m_page, this->m_maxQuranPages).c_str());
            this->m_textArea->setString(this->readPage(this->m_page).c_str());
        } else {
            this->m_page = 1;
            this->m_pageText->setString(fmt::format("{} page of {} pages", this->m_page, this->m_maxQuranPages).c_str());
            this->m_textArea->setString(this->readPage(this->m_page).c_str());
        }
    }
}