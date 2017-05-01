//
//  BarControllTouchComponent.cpp
//  CocosCreatorCppSample
//
//  Created by Kazuki Oda on 2017/05/01.
//
//

#include "BarControllTouchComponent.hpp"
USING_NS_CC;
#define EVENT(NAME) CC_CALLBACK_2(NAME, this)
RefPtr<BarControllTouchComponent> BarControllTouchComponent::create(
    cocos2d::Node *node) {
    RefPtr<BarControllTouchComponent> ptr;
    ptr.weakAssign(new BarControllTouchComponent);
    if (ptr->init(node)) {
        return ptr;
    }
    return nullptr;
}

bool BarControllTouchComponent::init(cocos2d::Node *node) {
    Component::init();
    setName("barControll");
    m_bar = node;
    return true;
}

void BarControllTouchComponent::onAdd() {
    Component::onAdd();
    m_touch = EventListenerTouchOneByOne::create();
    m_touch->onTouchBegan = EVENT(BarControllTouchComponent::onTouchBegan);
    m_touch->onTouchMoved = EVENT(BarControllTouchComponent::onTouchMoved);
    m_touch->onTouchEnded = EVENT(BarControllTouchComponent::onTouchEnded);
    m_touch->setSwallowTouches(true);
    auto dis = Director::getInstance()->getEventDispatcher();
    dis->addEventListenerWithSceneGraphPriority(m_touch, getOwner());
}

void BarControllTouchComponent::onRemove() {
    auto dis = Director::getInstance()->getEventDispatcher();
    dis->removeEventListener(m_touch);
    m_touch = nullptr;
    Component::onRemove();
}

bool BarControllTouchComponent::onTouchBegan(cocos2d::Touch *touch,
                                             cocos2d::Event *evt) {
    return true;
}

void BarControllTouchComponent::onTouchMoved(cocos2d::Touch *touch,
                                             cocos2d::Event *evt) {
    auto ownerSize = Director::getInstance()->getVisibleSize();
    auto barSize = m_bar->getContentSize();
    auto dPos = touch->getDelta();
    auto pos = m_bar->getPosition();
    pos.x += (dPos.x * 1.25f);

    if (pos.x - barSize.width * 0.5f < 0 ||
        pos.x + barSize.width * 0.5f > ownerSize.width) {
        return;
    }
    m_bar->setPosition(pos);
}

void BarControllTouchComponent::onTouchEnded(cocos2d::Touch *touch,
                                             cocos2d::Event *evt) {
}
