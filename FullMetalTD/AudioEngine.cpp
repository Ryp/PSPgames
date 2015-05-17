#include "AudioEngine.h"

AudioEngine::AudioEngine()
{
  initAudio();
  _sounds[CLICK] = loadSound("sfx/interface/click001.wav", 1);
}

AudioEngine::~AudioEngine()
{
  for (std::map<Sound, t_sound>::iterator i = _sounds.begin(); i != _sounds.end(); ++i) {
    oslDeleteSound((*i).second.sound_data);
  }
  endAudio();
}

void AudioEngine::playSound(Sound index)
{
  oslPlaySound(_sounds[index].sound_data, _sounds[index].channel);
}

void AudioEngine::playSound(Sound index, int channel)
{
  oslPlaySound(_sounds[index].sound_data, channel);
}

void AudioEngine::initAudio()
{
  oslInitAudio();
  oslSetQuitOnLoadFailure(1);
}

void AudioEngine::endAudio()
{
  oslDeinitAudio();
}

t_sound AudioEngine::loadSound(const char* filename, int channel)
{
  t_sound sound;
  sound.sound_data = oslLoadSoundFile(filename, OSL_FMT_NONE);
  sound.channel = channel;
  return sound;
}
