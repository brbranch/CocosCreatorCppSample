//
//  SampleGameController.cpp
//  CocosCreatorCppSample
//
//  Created by Kazuki Oda on 2017/05/01.
//
//

#include "SampleGameController.hpp"
#include "ControllerManager.hpp"
#include "audio/include/AudioEngine.h"
#include "component/BallBounceComponent.hpp"
#include "component/BarControllTouchComponent.hpp"
#include "component/BlockGameLogic.hpp"
#include "reader/CreatorReader.h"
USING_NS_CC;
#define EVT(NAME) CC_CALLBACK_1(NAME, this)

std::string SampleGameController::getFile() {
    return "SampleGame.ccreator";
}

void SampleGameController::setupScene(cocos2d::Scene *scene) {
    setClickListener("button", EVT(SampleGameController::onClickStartButton));
    experimental::AudioEngine::preload("bgm01.mp3");
    auto dispacher = Director::getInstance()->getEventDispatcher();
    auto listener = EventListenerCustom::create(
        "GAMEOVER", CC_CALLBACK_1(SampleGameController::gameOver, this));
    dispacher->addEventListenerWithSceneGraphPriority(listener, getScene());

    auto listener2 = EventListenerCustom::create(
        "ADDSCORE", CC_CALLBACK_1(SampleGameController::addScore, this));
    dispacher->addEventListenerWithSceneGraphPriority(listener2, getScene());

    experimental::AudioEngine::stopAll();

    // Cocos CreatorのVisible設定が反映されない。。。
    // そのため、最初に非表示にしとく
    for (auto s : {"player", "ball", "block", "gameover", "retry", "star"}) {
        if (auto l = utils::findChild(getScene(), s)) {
            l->setVisible(false);
        }
    }
}

void SampleGameController::onClickStartButton(cocos2d::Ref *ref) {
    auto button = static_cast<ui::Button *>(ref);
    button->removeFromParent();
    if (auto l = utils::findChild(getScene(), "description")) {
        l->removeFromParent();
    }
    startGame();
}

void SampleGameController::startGame() {
    experimental::AudioEngine::play2d("bgm01.mp3");
    auto s = getScene();
    auto game = utils::findChild(s, "game");
    auto logic = BlockGameLogic::create();
    logic->setStar(utils::findChild<Sprite *>(s, "star"));
    game->addComponent(logic);
    // これ不要だと思う…というよりどうしてかCocos
    // Creatorで空のNode作れなくなっちゃってる
    game->setCascadeOpacityEnabled(false);
    auto l = utils::findChild(s, "player");
    if (l) {
        logic->setBar(l);
        l->setVisible(true);
        s->addComponent(BarControllTouchComponent::create(l));
    }

    if (auto b = utils::findChild<Sprite *>(s, "block")) {
        logic->addSeed(b);
    }

    if (auto l = utils::findChild(s, "ball")) {
        l->setVisible(true);
        auto ball = BallBounceComponent::create();
        ball->setLogic(logic);
        l->addComponent(ball);
    }
}

void SampleGameController::dispose() {
    auto dispacher = Director::getInstance()->getEventDispatcher();
    dispacher->removeEventListenersForTarget(getScene());
    BaseController::dispose();
}

void SampleGameController::addScore(cocos2d::Event *event) {
    if (auto score = utils::findChild<Label *>(getScene(), "score")) {
        m_score += 100;
        auto str = StringUtils::format("%08d", m_score);
        score->setString(str);
    }
}

void SampleGameController::gameOver(cocos2d::Event *event) {
    for (auto s : {"gameover", "retry"}) {
        if (auto l = utils::findChild(getScene(), s)) {
            l->setVisible(true);
        }
    }
    setClickListener("retry", EVT(SampleGameController::onClickRetryButton));
}

void SampleGameController::onClickRetryButton(cocos2d::Ref *ref) {
    auto controller = SampleGameController::create();
    ControllerManager::getInstance()->setAndRun(controller);
}
