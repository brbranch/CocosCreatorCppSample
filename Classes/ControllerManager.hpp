//
//  ControllerManager.hpp
//  CocosCreatorCppSample
//
//  Created by Kazuki Oda on 2017/05/01.
//
//

#ifndef ControllerManager_hpp
#define ControllerManager_hpp

#include <stdio.h>
#include "IController.hpp"
#include "cocos2d.h"

class ControllerManager {
   private:
    cocos2d::RefPtr<IController> m_controller = nullptr;

   public:
    static ControllerManager* getInstance();
    /** Sceneを実行する */
    void setAndRun(IController* controller);
};

#endif /* ControllerManager_hpp */
