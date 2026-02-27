#include <.hpp>

#include <Geode/modify/CreatorLayer.hpp>
class $modify(CreatorLayerExt, CreatorLayer) {
    void later() {
		FMODAudioEngine::get()->playEffect(
            "explode_11/pipefalling.ogg", 0.5 + CCRANDOM_0_1(), CCRANDOM_0_1(), 1.0 + CCRANDOM_0_1()
        );
        if (CCRANDOM_0_1() > 0.5) onBack(this);
		if (CCRANDOM_0_1() > 0.5) Notification::create("wait for 2.21 you moron")->show();
		if (CCRANDOM_0_1() > 0.5) Notification::create("it's not here yet.")->show();
		if (CCRANDOM_0_1() > 0.5) Notification::create("out of order.")->show();
		if (CCRANDOM_0_1() > 0.5) Notification::create("check back in a few months or sumthin")->show();
		if (CCRANDOM_0_1() > 0.5) Notification::create("2.21's not out yet")->show();
        if (CCRANDOM_0_1() > 0.5) Notification::create("patience is a virtue")->show();
        if (CCRANDOM_0_1() > 0.5) Notification::create("please have patience.")->show();
    }
    void onAdventureMap(cocos2d::CCObject * sender) {
        later();
    }
    void onMultiplayer(cocos2d::CCObject* sender) {
        later();
    }
};