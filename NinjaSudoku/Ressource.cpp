#include "Ressource.h"
#include "constants.h"

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
  //Load Sounds
  //click_ = oslLoadSoundFileWAV("media/click.wav", OSL_FMT_NONE);
  //Load Images
  backgroundpic_ = oslLoadImageFileJPG((char*)"media/background.jpg", OSL_IN_RAM, OSL_PF_8888);
  bignumbers_ = oslLoadImageFilePNG((char*)"media/bignumbers.png", OSL_IN_RAM, OSL_PF_8888);
  oslSetImageFrameSize(bignumbers_, SU_CELL_SIZE, SU_CELL_SIZE);
  grid_ = oslLoadImageFilePNG((char*)"media/grid.png", OSL_IN_RAM, OSL_PF_8888);
  selected_ = oslLoadImageFilePNG((char*)"media/selected.png", OSL_IN_RAM, OSL_PF_8888);
  smallnumbers_ = oslLoadImageFilePNG((char*)"media/smallnumbers.png", OSL_IN_RAM, OSL_PF_8888);  
  oslSetImageFrameSize(smallnumbers_, SU_MINI_SIZE, SU_MINI_SIZE);
  //OSK Images
  osk_numbers_ = oslLoadImageFilePNG((char*)"media/osk_numbers.png", OSL_IN_RAM, OSL_PF_8888);  
  osk_back_ = oslLoadImageFilePNG((char*)"media/osk_back.png", OSL_IN_RAM, OSL_PF_8888);  
  osk_selected_ = oslLoadImageFilePNG((char*)"media/osk_selected.png", OSL_IN_RAM, OSL_PF_8888);  
  //Load font
  ltn_ = intraFontLoad("flash0:/font/ltn7.pgf",0);
}

Ressource::~Ressource()
{
  //oslDeleteSound(click_);
  oslDeleteImage(grid_);
  oslDeleteImage(backgroundpic_);
  intraFontUnload(ltn_);
}
