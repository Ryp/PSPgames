#ifndef __TIMER_H__
#define __TIMER_H__

#include <stdio.h>
#include <stdlib.h>

#include <oslib/oslib.h>

class Timer
{
private:
  clock_t start_clk_;
  clock_t temp_clk_;
  bool is_paused_;
  bool is_started_;
public:
  Timer();
  void startTimer();
  void pauseTimer();
  void addTimer(int t);
  int getTimer();
};

#endif
