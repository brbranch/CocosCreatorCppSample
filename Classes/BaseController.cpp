//
//  BaseController.cpp
//  CocosCreatorCppSample
//
//  Created by Kazuki Oda on 2017/05/01.
//
//

#include "BaseController.hpp"
USING_NS_CC;
static cocos2d::Size designResolutionSize = cocos2d::Size(640, 960);

Scene *BaseController::getScene() {
    return m_scene;
}

void BaseController::setup() {
    auto file = "creator/" + getFile();
    auto reader = creator::CreatorReader::createWithFilename(file);
    reader->setup();

    // 今のバージョンのCocos Creatorだと
    // setup時にResolutionPolicyがNO_BORDERになっちゃう。
    // 今後なおることを期待してとりあえずは手動で設定する。
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    director->setContentScaleFactor(1.0f);
    glview->setDesignResolutionSize(designResolutionSize.width,
                                    designResolutionSize.height,
                                    ResolutionPolicy::EXACT_FIT);

    m_scene = reader->getSceneGraph();
    setupScene(m_scene);
}

void BaseController::dispose() {
    m_scene = nullptr;
}

void BaseController::setClickListener(
    const std::string &name, const std::function<void(cocos2d::Ref *)> &event) {
    auto node = utils::findChild<ui::Button *>(m_scene, name);
    if (node == nullptr) {
        CCLOG("Warning node %s not found.", name.c_str());
        return;
    }
    node->addClickEventListener(event);
}
