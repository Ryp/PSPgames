#include "Ressource.h"
#include "rules.h"

Ressource * Ressource::Instance_ = 0;
Ressource * Ressource::GetInstance()
{
  if (!Instance_)
  {
    Instance_ = new Ressource;
  }
  return Instance_;
}

Ressource::Ressource()
{
  //Initialyze Mersenne twister context
  sceKernelUtilsMt19937Init(&ctx_, time(NULL));
  //Load Sounds
  click_ = oslLoadSoundFileWAV("media/click.wav", OSL_FMT_NONE);
  sonar_ = oslLoadSoundFileWAV("media/sonar.wav", OSL_FMT_NONE);
  win_ = oslLoadSoundFileWAV("media/win.wav", OSL_FMT_NONE);
  bomb_ = oslLoadSoundFileWAV("media/bomb.wav", OSL_FMT_NONE);
  //Load Images
  mousepic_ = oslLoadImageFilePNG((char*)"media/mouse.png", OSL_IN_RAM, OSL_PF_8888);
  tile_ = oslLoadImageFilePNG((char*)"media/tile.png", OSL_IN_RAM, OSL_PF_8888);
  oslSetImageFrameSize(tile_, TILE_SIZE+1, TILE_SIZE+1);
  heart_ = oslLoadImageFilePNG((char*)"media/heart.png", OSL_IN_RAM, OSL_PF_8888);
  heart_->x = 194;
  heart_->y = 256;
  backgroundpic_ = oslLoadImageFileJPG((char*)"media/background.jpg", OSL_IN_RAM, OSL_PF_8888);
  //Load font
  ltn_ = intraFontLoad("flash0:/font/ltn0.pgf",0);
}

Ressource::~Ressource()
{
  oslDeleteSound(click_);
  oslDeleteSound(sonar_);
  oslDeleteSound(win_);
  oslDeleteSound(bomb_);
  oslDeleteImage(mousepic_);
  oslDeleteImage(tile_);
  oslDeleteImage(heart_);
  oslDeleteImage(backgroundpic_);
  intraFontUnload(ltn_);
}

int Ressource::getRandomNum(int lo, int size)
{
  u32 rand_val = sceKernelUtilsMt19937UInt(&ctx_);
  rand_val = lo + rand_val % size;
  return (int)rand_val;
}

int blinkingEffect(int item, int flag)
{
  float temp;
  int alpha;
  if (item == flag) { //Item is choosed, so begin blinking
    temp = ((float)(clock() % CLOCKS_PER_SEC)) / ((float)CLOCKS_PER_SEC);
    alpha = (temp < 0.5f) ? (temp * 511) : ((1.0f - temp) * 511);
    return (0xFF<<24)+(alpha<<16)+(alpha<<8)+(alpha);
  }
  else
  {
    return 0xFF000000;
  }
}

void timeToText(int seconds, char *string)
{
  int sec, min;
  char tmin[10], tsec[5];
  sec = seconds % 60;
  min = (seconds - sec) / 60;
  if (sec < 10) {sprintf(tsec, "0%i", sec);} else {sprintf(tsec, "%i", sec);}
  if (min < 10) {sprintf(tmin, "0%i", min);} else {sprintf(tmin, "%i", min);}
  sprintf(string, "%s:%s", tmin, tsec);
}
