#include "Tebya/Audio.hpp"
#include <stdexcept>

namespace tebya {

// ------------------------------------------------------------------ Audio ---

Audio::Audio(const std::string &audio_path) {
  sound = Mix_LoadWAV(audio_path.c_str());
  if (!sound)
    throw std::runtime_error("Failed to load sound: " +
                             std::string(Mix_GetError()));
}

Audio::~Audio() {
  if (sound)
    Mix_FreeChunk(sound);
}

void Audio::play(bool loop) const {
  if (Mix_PlayChannel(-1, sound, loop ? -1 : 0) == -1)
    SDL_Log("Error playing sound: %s", Mix_GetError());
}

void Audio::setVolume(int volume) { Mix_VolumeChunk(sound, volume); }

// ------------------------------------------------------------------ Music ---

Music::Music(const std::string &audio_path) {
  music = Mix_LoadMUS(audio_path.c_str());
  if (!music)
    throw std::runtime_error("Failed to load music: " +
                             std::string(Mix_GetError()));
}

Music::~Music() {
  if (music)
    Mix_FreeMusic(music);
}

void Music::play(bool loop) const {
  if (Mix_PlayMusic(music, loop ? -1 : 0) == -1)
    SDL_Log("Error playing music: %s", Mix_GetError());
}

void Music::pause() const { Mix_PauseMusic(); }
void Music::resume() const { Mix_ResumeMusic(); }
void Music::stop() const { Mix_HaltMusic(); }

void Music::setVolume(int volume) { Mix_VolumeMusic(volume); }

bool Music::isPlaying() { return Mix_PlayingMusic() != 0; }

} // namespace tebya