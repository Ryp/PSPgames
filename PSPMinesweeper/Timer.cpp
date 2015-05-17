#include "Timer.h"

Timer::Timer()
{
  start_clk_ = 0;
  temp_clk_ = 0;
  is_paused_ = false;
  is_started_ = false;
}

void Timer::startTimer()
{
  is_started_ = true;
  is_paused_ = false;
  start_clk_ = clock() - temp_clk_ * CLOCKS_PER_SEC;
  temp_clk_ = 0;
}

void Timer::pauseTimer()
{
  if (!is_paused_) {
    is_paused_ = true;
    temp_clk_ = (clock() - start_clk_) / CLOCKS_PER_SEC;
  }
}

void Timer::addTimer(int t)
{
  start_clk_ -= (t * CLOCKS_PER_SEC);
}

int Timer::getTimer()
{
  if (!is_started_) {
    return 0;
  } else {
    if (is_paused_) {
      return temp_clk_;
    } else {
      return (int)((clock() - start_clk_) / CLOCKS_PER_SEC);
    }
  }
}
