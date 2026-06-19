#pragma once

#include <SDL2/SDL.h>
#include <cmath>

class AudioGenerator {
public:
  AudioGenerator(float frequency = 440.0f, int sampleRate = 44100)
      : frequency(frequency), sampleRate(sampleRate), phase(0.0f), audioId(0) {}

  ~AudioGenerator() { stop(); }

  bool init() {
    if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0) {
      SDL_Log("SDL audio init failed: %s", SDL_GetError());
      return false;
    }

    SDL_zero(desiredSpec);
    desiredSpec.freq = sampleRate;
    desiredSpec.format = AUDIO_F32;
    desiredSpec.channels = 1;
    desiredSpec.samples = 2048;
    desiredSpec.callback = audioCallback;
    desiredSpec.userdata = this;

    audioId = SDL_OpenAudioDevice(nullptr, 0, &desiredSpec, &obtainedSpec, 0);
    if (audioId == 0) {
      SDL_Log("Failed to open audio device: %s", SDL_GetError());
      return false;
    }

    return true;
  }

  void play() {
    if (audioId != 0) {
      SDL_PauseAudioDevice(audioId, 0);
    }
  }

  void stop() {
    if (audioId != 0) {
      SDL_PauseAudioDevice(audioId, 1);
      SDL_CloseAudioDevice(audioId);
      audioId = 0;
    }
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
  }

  void setFrequency(float newFrequency) { frequency = newFrequency; }

  float getFrequency() const { return frequency; }

  int getSampleRate() const { return obtainedSpec.freq; }

  void setVolume(float volumePercent) {
    // Clamp to 0-100 range
    volumePercent = (volumePercent < 0.0f)     ? 0.0f
                    : (volumePercent > 100.0f) ? 100.0f
                                               : volumePercent;

    // Convert percentage to SDL volume (0-128 scale)
    // 100% = 128, 50% = 64, 0% = 0
    volumeLevel = static_cast<int>(volumePercent * 1.28f);
  }

  float getVolume() const { return (volumeLevel / 128.0f) * 100.0f; }

private:
  static void audioCallback(void *userdata, Uint8 *stream, int len) {
    auto *gen = static_cast<AudioGenerator *>(userdata);
    float *fstream = reinterpret_cast<float *>(stream);
    int numSamples = len / sizeof(float);
    float phaseIncrement =
        2.0f * M_PI * gen->frequency / gen->obtainedSpec.freq;

    // Convert volume from SDL scale (0-128) to linear factor (0-1)
    float volumeFactor = gen->volumeLevel / 128.0f;

    for (int i = 0; i < numSamples; ++i) {
      // Generate sine wave with amplitude scaling and volume reduction
      fstream[i] = 0.3f * volumeFactor * std::sin(gen->phase);
      gen->phase += phaseIncrement;

      // Keep phase bounded to avoid precision loss
      if (gen->phase > 2.0f * M_PI) {
        gen->phase -= 2.0f * M_PI;
      }
    }
  }

  float frequency;
  int sampleRate;
  float phase;
  int volumeLevel = 128; // SDL volume scale: 0-128

  SDL_AudioDeviceID audioId;
  SDL_AudioSpec desiredSpec, obtainedSpec;
};