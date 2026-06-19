#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>

namespace tebya {

class Audio {
  Mix_Chunk *sound;

public:
  Audio(const std::string &audio_path);
  ~Audio();

  // no copy -- two objects freeing the same chunk = chaos
  Audio(const Audio &) = delete;
  Audio &operator=(const Audio &) = delete;

  void play(bool loop = false) const;
  void setVolume(int volume); // 0-128, MIX_MAX_VOLUME = 128
};

class Music {
  Mix_Music *music;

public:
  Music(const std::string &audio_path);
  ~Music();

  Music(const Music &) = delete;
  Music &operator=(const Music &) = delete;

  void play(bool loop = false) const;
  void pause() const;
  void resume() const;
  void stop() const;
  void setVolume(int volume); // 0-128
  static bool isPlaying();
};

} // namespace tebya