//
//  ControllerManager.cpp
//  CocosCreatorCppSample
//
//  Created by Kazuki Oda on 2017/05/01.
//
//

#include "ControllerManager.hpp"
USING_NS_CC;
static ControllerManager* s_instance = nullptr;
ControllerManager* ControllerManager::getInstance() {
    if (s_instance == nullptr) {
        s_instance = new ControllerManager;
    }
    return s_instance;
}

void ControllerManager::setAndRun(IController* controller) {
    if (m_controller == controller || controller == nullptr) {
        return;
    }
    if (m_controller) {
        m_controller->dispose();
    }
    m_controller = controller;
    m_controller->setup();
    auto scene = m_controller->getScene();
    auto director = Director::getInstance();
    if (director->getRunningScene() == nullptr) {
        director->runWithScene(scene);
        return;
    }
    director->replaceScene(scene);
}
