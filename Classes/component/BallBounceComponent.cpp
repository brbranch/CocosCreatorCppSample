//
//  BallBounceComponent.cpp
//  CocosCreatorCppSample
//
//  Created by Kazuki Oda on 2017/05/01.
//
//

#include "BallBounceComponent.hpp"
USING_NS_CC;
bool BallBounceComponent::init() {
    Component::init();
    setName("ball");
    m_delta = Point(100.0f, 480.0f);
    return true;
}

void BallBounceComponent::hit(const cocos2d::Point &vector) {
    m_delta = vector;
}

void BallBounceComponent::update(float f) {
    Component::update(f);
    if (m_logic) {
        m_logic->evaluate(this);
    }
    auto owner = getOwner();
    auto pos = getOwner()->getPosition();
    pos += Point(m_delta.x * f, m_delta.y * f);
    m_delta.y -= (100.0f * f);
    getOwner()->setPosition(pos);
    auto rotate = owner->getRotation();
    rotate -= 6.0f;
    if (rotate < 0.f) {
        rotate += 360.f;
    }
    owner->setRotation(rotate);
}

Rect BallBounceComponent::rect() {
    return getOwner()->getBoundingBox();
}
