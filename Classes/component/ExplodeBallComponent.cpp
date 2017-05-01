//
//  ExplodeBallComponent.cpp
//  CocosCreatorCppSample
//
//  Created by Kazuki Oda on 2017/05/01.
//
//

#include "ExplodeBallComponent.hpp"
USING_NS_CC;

bool ExplodeBallComponent::init() {
    Component::init();
    m_timer = br::Timer(0.5f);
    setName("explode");
    return true;
}

void ExplodeBallComponent::update(float f) {
    BallBounceComponent::update(f);
    m_timer.update(f);
    if (m_timer.isExpired()) {
        getOwner()->removeFromParent();
        return;
    }
}

void ExplodeBallComponent::hit(const cocos2d::Point &vector) {
    getOwner()->removeFromParent();
}
