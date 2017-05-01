//
//  BlockGameLogic.cpp
//  CocosCreatorCppSample
//
//  Created by Kazuki Oda on 2017/05/01.
//
//

#include "BlockGameLogic.hpp"
#include "BallBounceComponent.hpp"
#include "DropComponent.hpp"
#include "ExplodeBallComponent.hpp"
#include "audio/include/AudioEngine.h"
USING_NS_CC;

bool BlockGameLogic::init() {
    Component::init();
    setName("gamelogic");
    //    experimental::AudioEngine::preload("gun05.mp3");
    //    experimental::AudioEngine::preload("kaiten03.mp3");
    //    experimental::AudioEngine::preload("exp05.mp3");

    m_timer = br::Timer(1.0f, 1.0f);

    return true;
}

void BlockGameLogic::onAdd() {
    Component::onAdd();
}

void BlockGameLogic::evaluate(Ball *ball) {
    if (evaluateWall(ball)) {
        return;
    }
    if (evaluateBar(ball)) {
        return;
    }
    for (auto b : m_blocks) {
        if (evaluateNode(b, ball)) {
            destroyBlock(b);
            return;
        }
    }
}

void BlockGameLogic::destroyBlock(cocos2d::Sprite *b) {
    m_blocks.eraseObject(b);
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    // Androidはどうせ重くて動かなくなるからね、仕方ないね
    auto particle = ParticleSystemQuad::create("explode.plist");
    particle->setAutoRemoveOnFinish(true);
    particle->setPosition(b->getPosition());
    getOwner()->addChild(particle);
#endif

    auto dis = getOwner()->getEventDispatcher();
    dis->dispatchCustomEvent("ADDSCORE");

    //    int se = experimental::AudioEngine::play2d("gun05.mp3");
    //    experimental::AudioEngine::setVolume(se, 0.2f);
    if (m_star) {
        for (auto i = 45; i < 360; i += 90) {
            auto rad = CC_DEGREES_TO_RADIANS(i);
            auto pos = Point(cosf(rad) * 150.0f, sinf(rad) * 150.0f);
            addStarBall(pos, b->getPosition());
        }
    }

    b->removeFromParent();
}

void BlockGameLogic::addStarBall(const cocos2d::Point &speed,
                                 const cocos2d::Point &pos) {
    auto p = Sprite::createWithSpriteFrame(m_star->getSpriteFrame());
    p->setPosition(pos);
    auto component = ExplodeBallComponent::create();
    component->setDelta(speed);
    component->setLogic(this);
    p->addComponent(component);
    getOwner()->addChild(p);
}

void BlockGameLogic::addSeed(cocos2d::Sprite *node) {
    m_seeds.pushBack(node);
}

void BlockGameLogic::update(float f) {
    Component::update(f);
    if (m_bar == nullptr) return;
    // 出現
    static std::vector<std::vector<int>> s_map = {
        {1, 2, 3},    {2, 3, 4},    {3, 4, 5},   {4, 5, 6}, {7, 8, 9},
        {8, 9, 1},    {1, 3, 5},    {2, 4, 6},   {3, 5, 7}, {1, 2, 3, 4},
        {2, 3, 4, 5}, {3, 4, 5, 6}, {6, 7, 8, 9}};
    static auto mapSize = s_map.size();
    m_timer.update(f);

    if (m_timer.isExpired()) {
        if (m_timer.isIntervalOf(1)) {
            setBlock({1, 2, 3, 7, 8, 9});
            return;
        }
        auto vect = s_map[random(0, 100) % mapSize];
        setBlock(vect);
        m_timer.setMaxTime(MAX(m_timer.maxTime() - 0.01f, 0.5f));
    }

    // バーにりんごが当たってないか
    for (auto block : m_blocks) {
        if (m_bar->getBoundingBox().intersectsCircle(
                block->getPosition(), block->getContentSize().width * 0.5f)) {
            gameOver();
            return;
        }
    }
}

void BlockGameLogic::setBlock(const std::vector<int> &vect) {
    auto seed = m_seeds.getRandomObject();
    auto winSize = Director::getInstance()->getVisibleSize();
    for (auto v : vect) {
        auto s = Sprite::createWithSpriteFrame(seed->getSpriteFrame());
        auto pos = Point(0, winSize.height + s->getContentSize().height * 0.5f);
        pos.x = (winSize.width / 9.0f) * (v - 0.5f);
        s->setPosition(pos);
        s->addComponent(DropComponent::create());
        m_blocks.pushBack(s);
        getOwner()->addChild(s, 6);
    }
}

bool BlockGameLogic::evaluateWall(Ball *ball) {
    auto size = Director::getInstance()->getVisibleSize();
    auto rect = ball->rect();
    auto delta = ball->delta();
    if (rect.getMaxX() > size.width) {
        delta.x = MIN(-fabsf(delta.x), -30.f);
        ball->hit(delta);
        return true;
    }
    if (rect.getMinX() < 0) {
        delta.x = MAX(fabsf(delta.x), 30.0f);
        ball->hit(delta);
        return true;
    }
    if (rect.getMaxY() > size.height) {
        delta.y = MIN(-delta.y, -10.0f);
        ball->hit(delta);
        return true;
    }
    if (rect.getMinY() < 0 && ball->isMainBall()) {
        // ゲームオーバー
        gameOver();
        return true;
    }
    return false;
}

void BlockGameLogic::gameOver() {
    if (m_bar == nullptr) return;
    // experimental::AudioEngine::play2d("exp05.mp3");
    auto particle = ParticleSystemQuad::create("explode.plist");
    particle->setAutoRemoveOnFinish(true);
    particle->setPosition(m_bar->getPosition());
    getOwner()->addChild(particle);
    m_bar->removeFromParent();
    m_bar = nullptr;
    auto dispacher = Director::getInstance()->getEventDispatcher();
    dispacher->dispatchCustomEvent("GAMEOVER");
}

bool BlockGameLogic::evaluateBar(Ball *ball) {
    if (m_bar == nullptr) {
        return false;
    }
    if (evaluateNode(m_bar, ball)) {
        // 左よりか右よりかでより角度をつける
        auto ballX = ball->rect().getMidX();
        auto delta = ball->delta();
        auto pos = m_bar->getPosition();
        auto distance = fabsf(ballX - pos.x);
        if (distance < 20.0f) {
            //　中央付近なら特に補正しない
            return true;
        }
        distance = powf(distance, 1.3f);
        delta.x += pos.x > ballX ? -distance : distance;
        ball->hit(delta);
        // experimental::AudioEngine::play2d("kaiten03.mp3");
        return true;
    }
    return false;
}

bool BlockGameLogic::evaluateNode(cocos2d::Node *node, Ball *ball) {
    auto nodeRect = node->getBoundingBox();
    auto ballRect = ball->rect();
    auto delta = ball->delta();
    if (nodeRect.intersectsRect(ballRect)) {
        // 横に当たった
        if (nodeRect.getMinX() > ballRect.getMinX()) {
            delta.x = -delta.x - 50.0f;
        }
        if (nodeRect.getMaxX() < ballRect.getMaxX()) {
            delta.x = -delta.x + 50.0f;
        }
        // 縦に当たった
        if (nodeRect.getMaxY() < ballRect.getMaxY()) {
            delta.y = (-delta.y * 0.01f) + 480.0f;
        }
        if (nodeRect.getMinY() > ballRect.getMinY()) {
            delta.y = -delta.y - 20.0f;
        }
        ball->hit(delta);
        return true;
    }
    return false;
}
