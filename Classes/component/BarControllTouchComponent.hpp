//
//  BarControllTouchComponent.hpp
//  CocosCreatorCppSample
//
//  Created by Kazuki Oda on 2017/05/01.
//
//

#ifndef BarControllTouchComponent_hpp
#define BarControllTouchComponent_hpp

#include <stdio.h>
#include "cocos2d.h"

class BarControllTouchComponent : public cocos2d::Component {
   private:
    cocos2d::RefPtr<cocos2d::Node> m_bar;
    cocos2d::RefPtr<cocos2d::EventListenerTouchOneByOne> m_touch;

   public:
    static cocos2d::RefPtr<BarControllTouchComponent> create(
        cocos2d::Node* node);
    void onAdd() override;
    void onRemove() override;

   private:
    bool init(cocos2d::Node* node);
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* evt);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* evt);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* evt);
};

#endif /* BarControllTouchComponent_hpp */
