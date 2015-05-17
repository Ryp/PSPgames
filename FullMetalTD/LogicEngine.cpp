#include "LogicEngine.h"

void LogicEngine::notifyDeath()
{
  //TODO proper score calculation
  _score += 100;
}

void LogicEngine::notifyArrival()
{
  if (_lifes > 0) {
    --_lifes;
    if (_lifes == 0) {
      _status = LOST;
    }
  }
}

LogicEngine::LogicEngine()
{
  Target::registerObserver(this);
  _enemy_list = new std::list<Enemy>;
  _tower_list = new std::list<Tower*>;
  Tower::registerEnemyList(_enemy_list);
  
  //FIXME Pre-build some towers
//   _map_mgr._board[10][5].setTower(new Cannon(10, 5));
  _tower_list->push_back(new Cannon(10, 5));
  _tower_list->push_back(new Cannon(5, 5));
  _tower_list->push_back(new Cannon(8, 8));
  _tower_list->push_back(new Cannon(9, 2));
  //Sets all flags for a new game
  setNewGame("map/IronFortress.map");
}

LogicEngine::~LogicEngine() 
{
  delete _enemy_list;
  for (std::list<Tower*>::iterator i = _tower_list->begin(); i != _tower_list->end(); ++i) {
    delete (*i);
  }
  delete _tower_list;
}

void LogicEngine::update(OSL_CONTROLLER* pad)
{
  //Handle user input
  if (pad->pressed.start) {
    osl_quit = true;
  }    
  if (pad->analogY > ANALOG_DEAD_ZONE) {
    _viewport.zoom -= ZOOM_SPEED;
    if (_viewport.zoom < ZOOM_MIN) {_viewport.zoom = ZOOM_MIN;}
  }
  if (pad->analogY < -ANALOG_DEAD_ZONE) {
    _viewport.zoom += ZOOM_SPEED;
    if (_viewport.zoom > ZOOM_MAX) {_viewport.zoom = ZOOM_MAX;}
  }    
  if (pad->pressed.left) {
    if (_cursor.x > 0) {--_cursor.x;}
  }
  if (pad->pressed.right) {
    if (_cursor.x < (_map_mgr._size.x - 1)) {++_cursor.x;}
  }
  if (pad->pressed.up) {
    if (_cursor.y > 0) {--_cursor.y;}
  }
  if (pad->pressed.down) {
    if (_cursor.y < (_map_mgr._size.y - 1)) {++_cursor.y;}
  }
  if (_status == PLAYING) {
    if (pad->pressed.square) {
      _paused = !_paused;
    }
    if (pad->pressed.triangle) {
      if (_gamespeed < GAME_MAXSPEED) {
        ++_gamespeed;
      } else {
        _gamespeed = 1;
      }
    }
    if (pad->pressed.cross) {
      _audio_engine.playSound(CLICK);
      for (std::list<Enemy>::iterator i = _enemy_list->begin(); i != _enemy_list->end(); ++i) {
        (*i).setDamage(10);
      }
    }
    if (pad->pressed.cross) {
//       if (!_map_mgr._board[_cursor.x][_cursor.y].hasTower()) {
//         Cannon* t = new Cannon(_cursor.x, _cursor.y);
//         _map_mgr._board[_cursor.x][_cursor.y].setTower(t);
//       }
    }
    if (pad->pressed.L) {
      if (_towerselect == 1) {_towerselect = TOWER_NBR;} else {--_towerselect;}
    }
    if (pad->pressed.R) {
      if (_towerselect == TOWER_NBR) {_towerselect = 1;} else {++_towerselect;}
    }
    //Update AIs, projectiles and towers
    if (!_paused) {
      for (int i = 0; i < _gamespeed; ++i) {
        updateGame();
      }
    }
  }
  //Update viewport position and speed
  updateViewport();
  //Update cursor style
  updateCursor();
}

void LogicEngine::setNewGame(const char* mapname)
{
  //Load map
  _map_mgr.loadMap(mapname);
  //Set all vars
  _viewport.zoom = ZOOM_MIN;
  _viewport.origin.x = FIELD_WIDTH/2;
  _viewport.origin.y = FIELD_HEIGHT/2;
  _viewport.speed.x = 0;
  _viewport.speed.y = 0;
  _cursor.x = 0;
  _cursor.y = 0;
  _cursoralpha = 0;
  _towerselect = 1;
  _paused = true;
  _gamespeed = 1;
  _status = PLAYING;
  _lifes = STARTING_LIFES;
  _money = STARTING_MONEY;
  _points = STARTING_POINTS;
  _score = 0;
  _wave = 1;
  _wave_delay = WAVE_DELAY;
}

void LogicEngine::setNewWave()
{
  PathFinder astar;
  astar.findPath(_map_mgr.getBoard(), _map_mgr._size, _map_mgr._portals[1].first, _map_mgr._portals[1].second);
  _enemy_list->push_front(Enemy(_map_mgr._portals[1].first, 100, 0.05f, astar.getPath()));
  _enemy_list->push_front(Enemy(_map_mgr._portals[1].first, 100, 0.03f, astar.getPath()));
  astar.findPath(_map_mgr.getBoard(), _map_mgr._size, _map_mgr._portals[2].first, _map_mgr._portals[2].second);
  _enemy_list->push_front(Enemy(_map_mgr._portals[2].first, 100, 0.02f, astar.getPath()));
  _enemy_list->push_front(Enemy(_map_mgr._portals[2].first, 100, 0.04f, astar.getPath()));
}

void LogicEngine::updateViewport()
{
  int fzx = (PSP_SCR_WIDTH * VIEWPORT_FOCUS_ZONE) / (_viewport.zoom * 2); //Focuszone length
  int fzy = (PSP_SCR_HEIGHT * VIEWPORT_FOCUS_ZONE) / (_viewport.zoom * 2); //Focuszone width
  //Compute viewport speed
  if (getCursorScrPosX() < _viewport.origin.x - fzx) {
    _viewport.speed.x = getCursorScrPosX() - (_viewport.origin.x - fzx);
  }
  if (getCursorScrPosY() < _viewport.origin.y - fzy) {
    _viewport.speed.y = getCursorScrPosY() - (_viewport.origin.y - fzy);
  } 
  if (getCursorScrPosX() > _viewport.origin.x + fzx) {
    _viewport.speed.x = getCursorScrPosX() - (_viewport.origin.x + fzx);
  }
  if (getCursorScrPosY() > _viewport.origin.y + fzy) {
    _viewport.speed.y = getCursorScrPosY() - (_viewport.origin.y + fzy);
  }
  //Apply speed
  _viewport.origin.x += _viewport.speed.x * VIEWPORT_FRICTION;
  _viewport.origin.y += _viewport.speed.y * VIEWPORT_FRICTION;
  //Border detection for the viewport
  if (_viewport.origin.x < PSP_SCR_WIDTH / (_viewport.zoom * 2)) {
    _viewport.origin.x = PSP_SCR_WIDTH / (_viewport.zoom * 2);
  }
  if (_viewport.origin.y < PSP_SCR_HEIGHT / (_viewport.zoom * 2)) {
    _viewport.origin.y = PSP_SCR_HEIGHT / (_viewport.zoom * 2);
  } 
  if (_viewport.origin.x > FIELD_WIDTH - (PSP_SCR_WIDTH / (_viewport.zoom * 2))) {
    _viewport.origin.x = FIELD_WIDTH - (PSP_SCR_WIDTH / (_viewport.zoom * 2));
  }
  if (_viewport.origin.y > FIELD_HEIGHT - (PSP_SCR_HEIGHT / (_viewport.zoom * 2))) {
    _viewport.origin.y = FIELD_HEIGHT - (PSP_SCR_HEIGHT / (_viewport.zoom * 2));
  }
}

void LogicEngine::updateCursor()
{
  //TODO Update Style
  //Update cursor alpha
  _cursoralpha += CURSOR_BLINK_SPEED;
  if (_cursoralpha > 0x1FF) {
    _cursoralpha = 0;
  }
}

void LogicEngine::updateGame()
{
  //Update enemies
  for (std::list<Enemy>::iterator j = _enemy_list->begin(); j != _enemy_list->end(); ++j) {
    (*j).update();
  }
  //Between 2 waves
  if (_wave_delay > 0) {
    --_wave_delay;
    if (_wave_delay == 0) {
      //Delete all enemies
      _enemy_list->clear();
      setNewWave();
    }
  } else {
    //Check if all enemies are dead or arrived
    bool end = true; //Supposing current wave is ended
    for (std::list<Enemy>::iterator j = _enemy_list->begin(); j != _enemy_list->end(); ++j) {
      if ((!(*j).isDead()) && (!(*j).isArrived())) {
        end = false;
      }
    }
    if (end) {
      if (_wave == WAVE_MAX) {
        //All waves are complete
        _status = WON;
      } else {
        //Prepare next wave
        _wave_delay = WAVE_DELAY;
        ++_wave;
      }
    }
  }
  //Update towers
  for (std::list<Tower*>::iterator i = _tower_list->begin(); i != _tower_list->end(); ++i) {
    (*i)->update();
  }
}

float LogicEngine::getCursorScrPosX() const
{
  return _cursor.x * BOARD_CELL_SIZE + BOARD_OFFSETX;
}

float LogicEngine::getCursorScrPosY() const
{
  return _cursor.y * BOARD_CELL_SIZE + BOARD_OFFSETY;
}
