//
//  SampleGameController.hpp
//  CocosCreatorCppSample
//
//  Created by Kazuki Oda on 2017/05/01.
//
//

#ifndef SampleGameController_hpp
#define SampleGameController_hpp

#include <stdio.h>
#include "BaseController.hpp"

class SampleGameController : public BaseController {
   public:
    int m_score = 0;
    CREATE_FUNC(SampleGameController);

    void dispose() override;

   private:
    void setupScene(cocos2d::Scene* scene) override;
    std::string getFile() override;
    void onClickStartButton(cocos2d::Ref* ref);
    void startGame();
    void gameOver(cocos2d::Event* event);
    void addScore(cocos2d::Event* event);
    void onClickRetryButton(cocos2d::Ref* ref);
};

#endif /* SampleGameController_hpp */
