#include "GraphicEngine.h"
#include "psppower.h"

GraphicEngine::GraphicEngine(LogicEngine* logic_engine)
{
  //Register engine class
  _logic_engine = logic_engine;
  //Initialize the OSLib
  oslInitGfx(OSL_PF_8888, 1);
  oslSetBilinearFilter(1);
  oslSetQuitOnLoadFailure(1);
  //FIXME console-like text
  oslSetTextColor(WHITE);
  oslSetBkColor(TRANSPARENT);
  //Load image data
  _textures[DEBUG_CELLMARKER] = oslLoadImageFilePNG((char*)"media/cell.png", OSL_IN_RAM, OSL_PF_8888);
  _textures[UI_CURSOR_NORMAL] = oslLoadImageFilePNG((char*)"media/mouse.png", OSL_IN_RAM, OSL_PF_8888);
  _textures[E_BOO] = oslLoadImageFilePNG((char*)"media/enemy32.png", OSL_IN_RAM, OSL_PF_8888);
  _textures[T_CANNON] = oslLoadImageFilePNG((char*)"media/tower64.png", OSL_IN_RAM, OSL_PF_8888);
  //FIXME test
  _textures[T_CANNON]->centerX = 32;
  _textures[T_CANNON]->centerY = 32;
  _textures[E_BOO]->centerX = 16;
  _textures[E_BOO]->centerY = 16;
  _textures[DEBUG_CELLMARKER]->centerX = 4;
  _textures[DEBUG_CELLMARKER]->centerY = 4;
}

GraphicEngine::~GraphicEngine()
{
  for (std::map<Tex, t_image>::iterator i = _textures.begin(); i != _textures.end(); ++i) {
    oslDeleteImage((*i).second);
  }
  oslEndGfx();
}

void GraphicEngine::render()
{
  //Start drawing
  oslStartDrawing();
  oslClearScreen(RGB(0, 0, 0));
  //DEBUG
  for (int i = 0; i < _logic_engine->_map_mgr._size.x; ++i) {
    for (int j = 0; j < _logic_engine->_map_mgr._size.y; ++j) {
      drawImageXYWithZoom(_textures[DEBUG_CELLMARKER], i * BOARD_CELL_SIZE + BOARD_OFFSETX, j * BOARD_CELL_SIZE + BOARD_OFFSETY);
    }
  }
  //Draw enemies
  _logic_engine->_enemy_list->sort();
  for (std::list<Enemy>::iterator i = _logic_engine->_enemy_list->begin(); i != _logic_engine->_enemy_list->end(); ++i) {
    //Draw sprite
    drawImageXYAlphaWithZoom(_textures[E_BOO], (*i).getAlpha(), (*i).getPosX() * BOARD_CELL_SIZE + BOARD_OFFSETX, (*i).getPosY() * BOARD_CELL_SIZE + BOARD_OFFSETY);
    if (!(*i).isDead() && !(*i).isArrived()) {
      drawRectWithZoom((*i).getPosX() * BOARD_CELL_SIZE + BOARD_OFFSETX - HP_WIDTH / 2,
                       (*i).getPosY() * BOARD_CELL_SIZE + BOARD_OFFSETY - (HP_OFFSETY + HP_HEIGHT),
                       (*i).getPosX() * BOARD_CELL_SIZE + BOARD_OFFSETX + HP_WIDTH / 2,
                       (*i).getPosY() * BOARD_CELL_SIZE + BOARD_OFFSETY - HP_OFFSETY,
                       RED
      );
      drawRectWithZoom((*i).getPosX() * BOARD_CELL_SIZE + BOARD_OFFSETX - HP_WIDTH / 2,
                       (*i).getPosY() * BOARD_CELL_SIZE + BOARD_OFFSETY - (HP_OFFSETY + HP_HEIGHT),
                       (*i).getPosX() * BOARD_CELL_SIZE + BOARD_OFFSETX - HP_WIDTH / 2 + HP_WIDTH * ((float)(*i).getHp() / (float)(*i).getMaxHp()),
                       (*i).getPosY() * BOARD_CELL_SIZE + BOARD_OFFSETY - HP_OFFSETY,
                       GREEN
      );
      //Draw HP left FIXME
      char temp_text[40];
      sprintf(temp_text, "%iHp", (*i).getHp());
      drawStringWithZoom((*i).getPosX() * BOARD_CELL_SIZE + BOARD_OFFSETX - 10, (*i).getPosY() * BOARD_CELL_SIZE + BOARD_OFFSETY - 20, temp_text);
    }
  }
  //Draw towers
//   for (int i = 0; i < _logic_engine->_map_mgr._size.x; ++i) {
//     for (int j = 0; j < _logic_engine->_map_mgr._size.y; ++j) {
//       if (_logic_engine->_map_mgr._board[i][j].hasTower()) {
//         
//       }
//     }
//   }
  for (std::list<Tower*>::iterator i = _logic_engine->_tower_list->begin(); i != _logic_engine->_tower_list->end(); ++i) {
    _textures[T_CANNON]->angle = ((*i)->getAngle() * 360) / (M_PI * 2);
    drawImageXYWithZoom(_textures[T_CANNON], (*i)->getPosX() * BOARD_CELL_SIZE + BOARD_OFFSETX, (*i)->getPosY() * BOARD_CELL_SIZE + BOARD_OFFSETY);
  }
  //Draw cursor
  drawImageXYAlphaWithZoom(_textures[UI_CURSOR_NORMAL], abs(0xFF - _logic_engine->_cursoralpha), _logic_engine->getCursorScrPosX(), _logic_engine->getCursorScrPosY());
  //FIXME Debug OSD
  char temp_text[40];
  oslDrawString(200, 130, (osl_quit) ? ("EXITING...") : (""));
  sprintf(temp_text, "Money: %i$", _logic_engine->_money);
  oslDrawString(200, 0, temp_text);
  sprintf(temp_text, "Points: %ip", _logic_engine->_points);
  oslDrawString(300, 0, temp_text);
  oslDrawString(300, 8, (_logic_engine->_paused) ? ("PAUSED") : (""));
  sprintf(temp_text, "Score: %i", _logic_engine->_score);
  oslDrawString(400, 0, temp_text);
  sprintf(temp_text, "Lifes: %i", _logic_engine->_lifes);
  oslDrawString(400, 8, temp_text);
  sprintf(temp_text, "CursorX: %i", _logic_engine->_cursor.x);
  oslDrawString(0, 0, temp_text);
  sprintf(temp_text, "CursorY: %i", _logic_engine->_cursor.y);
  oslDrawString(0, 8, temp_text);
  sprintf(temp_text, "TowSelect: %i", _logic_engine->_towerselect);
  oslDrawString(0, 16, temp_text);
  sprintf(temp_text, "Speed: %i", _logic_engine->_gamespeed);
  oslDrawString(0, 24, temp_text);
  sprintf(temp_text, "fOpen: %i", _logic_engine->_map_mgr.isLoaded());
  oslDrawString(0, 32, temp_text);
  OSL_MEMSTATUS ram = oslGetRamStatus();
  sprintf(temp_text, "Ram: %i", ram.maxAvailable);
  oslDrawString(0, 40, temp_text);
  if (scePowerGetBatteryLifePercent() >= 0) {
    sprintf(temp_text, "Battery: %i%%", scePowerGetBatteryLifePercent());
    oslDrawString(0, 48, temp_text);
  }
  sprintf(temp_text, "Wave: %i", _logic_engine->_wave);
  oslDrawString(0, 56, temp_text);
  sprintf(temp_text, "WaveDelay: %i", _logic_engine->_wave_delay);
  oslDrawString(0, 64, temp_text);
  sprintf(temp_text, "Status: %i", _logic_engine->_status);
  oslDrawString(0, 72, temp_text);
  //Finish drawing
  oslEndDrawing();
}

void GraphicEngine::drawStringWithZoom(int a, int b, const char* str)
{
  oslDrawString((a - _logic_engine->_viewport.origin.x) * _logic_engine->_viewport.zoom + PSP_SCR_WIDTH/2, 
                (b - _logic_engine->_viewport.origin.y) * _logic_engine->_viewport.zoom + PSP_SCR_HEIGHT/2,
                str
  );
}

void GraphicEngine::drawLineWithZoom(int a, int b, int u, int v, t_color color)
{
  oslDrawLine((a - _logic_engine->_viewport.origin.x) * _logic_engine->_viewport.zoom + PSP_SCR_WIDTH/2,
              (b - _logic_engine->_viewport.origin.y) * _logic_engine->_viewport.zoom + PSP_SCR_HEIGHT/2,
              (u - _logic_engine->_viewport.origin.x) * _logic_engine->_viewport.zoom + PSP_SCR_WIDTH/2,
              (v - _logic_engine->_viewport.origin.y) * _logic_engine->_viewport.zoom + PSP_SCR_HEIGHT/2,
              color
  );
}

void GraphicEngine::drawRectWithZoom(int a, int b, int u, int v, t_color color)
{
  oslDrawFillRect((a - _logic_engine->_viewport.origin.x) * _logic_engine->_viewport.zoom + PSP_SCR_WIDTH/2,
                  (b - _logic_engine->_viewport.origin.y) * _logic_engine->_viewport.zoom + PSP_SCR_HEIGHT/2,
                  (u - _logic_engine->_viewport.origin.x) * _logic_engine->_viewport.zoom + PSP_SCR_WIDTH/2,
                  (v - _logic_engine->_viewport.origin.y) * _logic_engine->_viewport.zoom + PSP_SCR_HEIGHT/2,
                  color
  );
}

void GraphicEngine::drawImageXYWithZoom(t_image image, int x, int y)
{
  image->stretchX = (int) (image->sizeX * _logic_engine->_viewport.zoom);
  image->stretchY = (int) (image->sizeY * _logic_engine->_viewport.zoom);
  oslDrawImageXY(image, 
                 (x - _logic_engine->_viewport.origin.x) * _logic_engine->_viewport.zoom + PSP_SCR_WIDTH/2, 
                 (y - _logic_engine->_viewport.origin.y) * _logic_engine->_viewport.zoom + PSP_SCR_HEIGHT/2
  );
}

void GraphicEngine::drawImageXYAlphaWithZoom(t_image image, int alpha, int x, int y)
{
  oslSetAlpha(OSL_FX_ALPHA, alpha); //Turn transparency on
  drawImageXYWithZoom(image, x, y);
  oslSetAlpha(OSL_FX_RGBA, alpha); //Turn transparency off
}
