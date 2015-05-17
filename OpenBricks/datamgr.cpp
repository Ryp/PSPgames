#include "datamgr.h"

Options getGameConfig()
{
  Options tmp;
  std::ifstream myfile;
  std::string line;
  myfile.open("cfg/game.cfg", std::ios::in);
  if (myfile.is_open()) {
    getline(myfile, line);
    tmp.flags = line[0];
    tmp.brick_type = 1; // FIXME
    myfile.close();
  } else {
    tmp = getDefaultGameConfig();
  }
  return tmp;
}

Options getDefaultGameConfig()
{
  Options tmp;
  tmp.flags = ~OPT_SOFT_DROP;
  tmp.brick_type = 0;
  return tmp;
}

bool writeGameConfigFile(const Options& source)
{
  bool success;
  std::ofstream myfile;
  myfile.open("cfg/game.cfg", std::ios::out);
  if (myfile.is_open()) {
    myfile << source.flags << std::endl;
    myfile.close();
    success = true;
  } else {
    success = false;
  }
  return success;
}

bool isMemoryStickPresent()
{
  return MScmIsMediumInserted();
}
