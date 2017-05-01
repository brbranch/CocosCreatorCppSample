//
//  DropComponent.hpp
//  CocosCreatorCppSample
//
//  Created by Kazuki Oda on 2017/05/01.
//
//

#ifndef DropComponent_hpp
#define DropComponent_hpp

#include <stdio.h>
#include "cocos2d.h"

/** 落ちていく動きを定義するコンポーネント */
class DropComponent : public cocos2d::Component {
   private:
    float m_speed = 0.f;

   public:
    CREATE_FUNC(DropComponent);
    void update(float f) override;

   private:
    bool init() override;
};

#endif /* DropComponent_hpp */
