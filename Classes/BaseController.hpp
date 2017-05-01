//
//  BaseController.hpp
//  CocosCreatorCppSample
//
//  Created by Kazuki Oda on 2017/05/01.
//
//

#ifndef BaseController_hpp
#define BaseController_hpp

#include <stdio.h>
#include "IController.hpp"
#include "reader/CreatorReader.h"

class BaseController : public IController {
   private:
    cocos2d::RefPtr<cocos2d::Scene> m_scene;

   public:
    cocos2d::Scene* getScene() override;
    void setup() override;
    void dispose() override;

   protected:
    void setClickListener(const std::string& name,
                          const std::function<void(cocos2d::Ref*)>& event);
    virtual std::string getFile() = 0;
    virtual void setupScene(cocos2d::Scene* scene) = 0;
};

#endif /* BaseController_hpp */
