//
//  ExplodeBallComponent.hpp
//  CocosCreatorCppSample
//
//  Created by Kazuki Oda on 2017/05/01.
//
//

#ifndef ExplodeBallComponent_hpp
#define ExplodeBallComponent_hpp

#include <stdio.h>
#include "BallBounceComponent.hpp"
#include "BlockGameLogic.hpp"
#include "cocos2d.h"
#include "core/Timer.hpp"

/** 破壊時に出るボールの動きを定義するコンポーネント */
class ExplodeBallComponent : public BallBounceComponent {
   private:
    br::Timer m_timer;

   public:
    CREATE_FUNC(ExplodeBallComponent);
    void update(float f) override;
    void hit(const cocos2d::Point& vector) override;
    bool isMainBall() override {
        return false;
    }

   private:
    bool init() override;
};

#endif /* ExplodeBallComponent_hpp */
