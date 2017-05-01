//
//  BlockGameLogic.hpp
//  CocosCreatorCppSample
//
//  Created by Kazuki Oda on 2017/05/01.
//
//

#ifndef BlockGameLogic_hpp
#define BlockGameLogic_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "core/Timer.hpp"
class Ball;
class BlockGameLogic : public cocos2d::Component {
   private:
    CC_SYNTHESIZE(cocos2d::RefPtr<cocos2d::Node>, m_bar, Bar);
    CC_SYNTHESIZE(cocos2d::RefPtr<cocos2d::Sprite>, m_star, Star);
    cocos2d::Vector<cocos2d::Sprite*> m_blocks;
    cocos2d::Vector<cocos2d::Sprite*> m_seeds;
    bool m_isGameOver = false;
    br::Timer m_timer;

   public:
    CREATE_FUNC(BlockGameLogic);
    void evaluate(Ball* ball);
    void addSeed(cocos2d::Sprite* node);
    void update(float f) override;
    void onAdd() override;

   private:
    void setBlock(const std::vector<int>& vect);
    void gameOver();
    bool init() override;
    bool evaluateWall(Ball* ball);
    bool evaluateBar(Ball* ball);
    bool evaluateNode(cocos2d::Node* node, Ball* ball);
};

#endif /* BlockGameLogic_hpp */
