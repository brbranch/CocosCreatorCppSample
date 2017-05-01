//
//  BallBounceComponent.hpp
//  CocosCreatorCppSample
//
//  Created by Kazuki Oda on 2017/05/01.
//
//

#ifndef BallBounceComponent_hpp
#define BallBounceComponent_hpp

#include <stdio.h>
#include "BlockGameLogic.hpp"
#include "cocos2d.h"

class Ball {
   public:
    virtual ~Ball(){};
    virtual void hit(const cocos2d::Point& vector) = 0;
    virtual cocos2d::Point delta() = 0;
    virtual cocos2d::Rect rect() = 0;
    virtual bool isMainBall() {
        return true;
    }
};

class BallBounceComponent : public cocos2d::Component, public Ball {
   private:
    CC_SYNTHESIZE(cocos2d::Point, m_delta, Delta);
    CC_SYNTHESIZE(cocos2d::RefPtr<BlockGameLogic>, m_logic, Logic);

   public:
    CREATE_FUNC(BallBounceComponent);
    void hit(const cocos2d::Point& vector) override;
    cocos2d::Point delta() override {
        return m_delta;
    };
    cocos2d::Rect rect() override;
    void update(float f) override;

   private:
    bool init() override;
};

#endif /* BallBounceComponent_hpp */
