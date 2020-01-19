#ifndef SIMPLETIMER_H
#define SIMPLETIMER_H

class SimpleTimer
{
public :
 SimpleTimer(float timerMax);

 void setTimer(float timerMax);

 float getTime() const;
 float getMaxTime() const;

 bool operator() (float time) const;

private:
 float timerMax_;
 mutable float time_;

};

#endif

