//
//  IController.hpp
//  CocosCreatorCppSample
//
//  Created by Kazuki Oda on 2017/05/01.
//
//

#ifndef IController_h
#define IController_h
#include "cocos2d.h"

class IController : public cocos2d::Ref {
   public:
    virtual ~IController(){};
    virtual cocos2d::Scene* getScene() = 0;
    virtual void setup() = 0;
    virtual void dispose() = 0;

   protected:
    virtual bool init() {
        return true;
    }
};

#endif /* IController_h */
