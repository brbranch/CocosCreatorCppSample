//
//  DropComponent.cpp
//  CocosCreatorCppSample
//
//  Created by Kazuki Oda on 2017/05/01.
//
//

#include "DropComponent.hpp"
USING_NS_CC;

bool DropComponent::init() {
    Component::init();
    setName("drop");
    return true;
}

void DropComponent::update(float f) {
    auto owner = getOwner();
    auto pos = owner->getPosition();
    pos.y -= m_speed;
    m_speed += (0.9f * f);
    owner->setPosition(pos);
    auto rotate = owner->getRotation();
    rotate += 3.0f;
    if (rotate > 360.f) {
        rotate -= 360.f;
    }
    owner->setRotation(rotate);
}
