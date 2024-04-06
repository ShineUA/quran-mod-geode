#include <Geode/Geode.hpp>
#include "layers/ReadLayer.h"

using namespace geode::prelude;


#include <Geode/modify/MenuLayer.hpp>
class $modify(MyMenuLayer, MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) {
			return false;
		}

		auto readButton = CCMenuItemSpriteExtra::create(
			CCSprite::create("AK_bookBtn_001.png"_spr),
			this,
			menu_selector(MyMenuLayer::onMyButton)
		);

		auto menu = this->getChildByID("bottom-menu");
		menu->addChild(readButton);

		readButton->setID("read-button"_spr);

		menu->updateLayout();

		return true;
	}

	void onMyButton(CCObject* sender) {
		CCScene::get()->addChild(ReadLayer::create());
	}
};
