#include "MapMgr.h"

MapMgr::MapMgr()
{
  _loaded = false;
}

MapMgr::~MapMgr() 
{
  if (_loaded) {
    deleteBoard();
  }
}

void MapMgr::loadMap(const char* filename)
{
  if (_loaded) {
    _portals.clear();
    _walls.clear();
    _wave_list.clear();
    deleteBoard();
  }
  if (!(_fd = sceIoOpen(filename, O_RDONLY, 0777))) {
    std::cerr << "Error: Couldn't load mapfile" << std::endl;
    _loaded = false;
  } else {
    //TODO Read from real file
    _size.x = 22;
    _size.y = 12;
    t_2dindex start = {0, 0};
    t_2dindex dest = {9, 9};
    
    _portals[1] = std::pair< t_2dindex, t_2dindex >(start, dest);
    
    t_2dindex s = {9, 9};
    t_2dindex d = {0, 4};
    
    _portals[2] = std::pair< t_2dindex, t_2dindex >(s, d);
    
    t_2dindex ignore1 = {8, 8};
    t_2dindex ignore2 = {9, 8};
    t_2dindex ignore3 = {9, 0};
    _walls.push_front(ignore1);
    _walls.push_front(ignore2);
    _walls.push_front(ignore3);
    
    t_wave wave1;
    wave1.waveNo = 1;
    wave1.portalNo = 1;
    wave1.type = GRUNT;
    wave1.count = 5;
    wave1.delay = 20;
    wave1.rate = 60;
    t_wave wave2;
    wave2.waveNo = 2;
    wave2.portalNo = 1;
    wave2.type = GRUNT;
    wave2.count = 2;
    wave2.delay = 10;
    wave2.rate = 120;
    t_wave wave3;
    wave3.waveNo = 3;
    wave3.portalNo = 1;
    wave3.type = GRUNT;
    wave3.count = 10;
    wave3.delay = 0;
    wave3.rate = 80;
    _wave_list.push_back(wave1);
    _wave_list.push_back(wave2);
    _wave_list.push_back(wave3);
    
    allocBoard();
    //Set ignored cells
    for (std::list<t_2dindex>::iterator i = _walls.begin(); i != _walls.end(); ++i) {
      _board[i->x][i->y].setBlocked(true);
    }
    _loaded = true;
  }
}

bool MapMgr::isLoaded() const
{
  return _loaded;
}

GameCell** MapMgr::getBoard() const
{
  return _board;
}

void MapMgr::allocBoard()
{
  //Alloc board with default constructor
  _board = new GameCell*[_size.x];
  for (int i = 0; i < _size.x; ++i) {
    _board[i] = new GameCell[_size.y];
  }
}

void MapMgr::deleteBoard()
{
  for (int i = 0; i < _size.x; ++i) {
    delete[] _board[i];
  }
  delete[] _board;
}
