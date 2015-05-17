/*
 * AudioEngine.h 
 * 
 * Copyright 2012 Ryp (ryp.sqrt@gmail.com)
 * 
 * https://github.com/Ryp/FullMetalTD
 * 
 * FullMetalTD is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * FullMetalTD is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __AUDIOENGINE_H__
#define __AUDIOENGINE_H__

#include <oslib/oslib.h>
#include <map>

enum Sound {
  CLICK
};

typedef struct {
  OSL_SOUND* sound_data;
  int channel;
} t_sound;

class AudioEngine
{
public:
  AudioEngine();
  ~AudioEngine();
  void playSound(Sound index);
  void playSound(Sound index, int channel);
private:
  void initAudio();
  void endAudio();
  t_sound loadSound(const char* filename, int channel);
  
  std::map<Sound, t_sound> _sounds;
};

#endif
