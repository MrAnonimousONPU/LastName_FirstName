#include "SimpleTimer.h"

SimpleTimer::SimpleTimer(float timerMax) : 
 timerMax_(timerMax),
 time_(timerMax_)
{
}

void SimpleTimer::setTimer(float timerMax)
{
 timerMax_ = timerMax;
 time_ = timerMax;
}

float SimpleTimer::getTime() const
{
 return time_;
}

float SimpleTimer::getMaxTime() const
{
 return timerMax_;
}

bool SimpleTimer::operator()(float time) const
{
 time_ -= time;
 if (time_ < 0)
 {
  time_ = timerMax_;
  return true;
 }
 return false;
}
