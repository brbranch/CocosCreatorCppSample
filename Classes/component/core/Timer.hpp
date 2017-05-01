//
//  Timer.hpp
//  CocosCreatorCppSample
//
//  Created by Kazuki Oda on 2017/05/01.
//
//

#ifndef Timer_hpp
#define Timer_hpp

#include <stdio.h>
namespace br {
class Timer {
   private:
    long m_time = 0;
    float m_nowTime;
    float m_maxTime;

   public:
    Timer(float nowTime, float maxTime)
        : m_nowTime(nowTime), m_maxTime(maxTime){};
    Timer() : Timer(0, 0){};
    Timer(float maxTime) : Timer(0, maxTime){};
    bool isIntervalOf(long time);
    float nowTime() const;
    float maxTime() const;
    void setMaxTime(float maxTime);
    void update(float f);
    bool isExpired(bool autoReset = true);
    float percentage();
    void reset();
};
}

#endif /* Timer_hpp */
