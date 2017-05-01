//
//  Timer.cpp
//  CocosCreatorCppSample
//
//  Created by Kazuki Oda on 2017/05/01.
//
//

#include "Timer.hpp"
namespace br {

bool Timer::isExpired(bool autoReset) {
    auto expired = m_maxTime <= m_nowTime;
    if (expired) {
        m_time++;
    }
    if (expired && autoReset) {
        reset();
    }
    return expired;
}

void Timer::setMaxTime(float maxTime) {
    m_maxTime = maxTime;
}

void Timer::update(float f) {
    m_nowTime += f;
}

void Timer::reset() {
    m_nowTime = 0.0f;
}

float Timer::maxTime() const {
    return m_maxTime;
}
float Timer::nowTime() const {
    return m_nowTime;
}
bool Timer::isIntervalOf(long time) {
    return time == m_time;
}

float Timer::percentage() {
    if (m_maxTime <= 0) return 0;
    return (m_nowTime / m_maxTime) * 100.0f;
}
}
