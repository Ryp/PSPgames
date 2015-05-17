#include "Save.h"

Savemanager::Savemanager()
{
  data_ = fopen("ms.data", "r+");
  loaded_ = !(data_ == NULL);
  if (loaded_) {
    fseek(data_, 0, SEEK_SET);
    for (int i=0; i<6; i++) {
      fscanf(data_, "%i;", &scores_.classic[i]);
    }
  }
}

Savemanager::~Savemanager()
{
  if (loaded_) {
    fclose(data_);
  }
}

bool Savemanager::checkHighscore(int score, char level, char mode)
{
  bool newhi;
  if ((loaded_) && (level != CUSTOM)) {
    if (scores_.classic[(level-1)+mode*3] > score) {
      newhi = true;
      scores_.classic[(level-1)+mode*3] = score;
      fseek(data_, 0, SEEK_SET);
      for (int i=0; i<6; i++) {
        fprintf(data_, "%i;", scores_.classic[i]);
      }
    } else {
      newhi = false;
    }
  } else {
    newhi = false;
  }
  return newhi;
}

scoreboard Savemanager::getHighscores()
{
  return scores_;
}

bool Savemanager::isLoaded()
{
  return loaded_;
}
