#pragma once
#include <.hpp>

#include <Geode/modify/CCMenuItem.hpp>
class $modify(PopupChihuahua, CCMenuItem) {
    inline static bool can_asd = false;
    inline static std::function<void()> onClick = []() {};
    static auto createPopup() {
        auto popup = createQuickPopup("", "", "", "", [](auto, auto) { 
            PopupChihuahua::onClick();
            }, false);
        popup->m_mainLayer->removeAllChildrenWithCleanup(0);
        popup->m_mainLayer->addChild(popup->m_buttonMenu);
        popup->m_button1->getParent()->setContentSize(CCSize(1, 1) * 7777);
        popup->m_button1->setVisible(0);
        popup->m_button2->setVisible(0);
        auto sprite = CCSprite::create("Gidget_Taco_Bell_chihuahua_jpg_2026-03-01_13.38.19.png");
        popup->m_mainLayer->addChild(sprite);
        sprite->setPosition(popup->getContentSize() / 2);
        sprite->setScaleX((popup->getContentSize().width) / sprite->getContentSize().width);
        sprite->setScaleY((popup->getContentSize().height) / sprite->getContentSize().height);
        return popup;
    };
    $override void activate() {
        if (getMod()->getSettingValue<bool>("gidget?")) {
            if (string::containsAny(this->getID(), { "play-button", "level-button" })) {
                srand(time(0));
                if (CCRANDOM_0_1() > 0.4) {
                    auto pop = createPopup();
                    pop->show();
                    PopupChihuahua::onClick = [this]()
                        {
                            GameManager::get()->playMenuMusic();
                            return CCMenuItem::activate();
                        };
                    GameManager::get()->fadeInMusic("TBGidgetCommercial.mp3");
                    return;
                }
            };
        };
        return CCMenuItem::activate();
    }
};