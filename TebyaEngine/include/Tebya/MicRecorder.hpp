#pragma once
// MicRecorder.hpp
// Dark magic: manually crafting a WAV header like it's 1991
// Simple magic: the rest of it

#include <SDL2/SDL.h>
#include <cstdint>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace tebya {

class MicRecorder {
public:
  struct Config {
    int freq = 44100;
    uint8_t channels = 1;
    uint16_t samples = 4096; // buffer size
  };

  explicit MicRecorder(Config cfg = {44100, 1, 4096}) : m_cfg(cfg) {
    if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
      throw std::runtime_error(SDL_GetError());
  }

  ~MicRecorder() {
    if (isOpen())
      SDL_CloseAudioDevice(m_device);
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
  }

  // No copies — owning a hardware device is not a group activity
  MicRecorder(const MicRecorder &) = delete;
  MicRecorder &operator=(const MicRecorder &) = delete;

  void open(const char *device_name = nullptr) {
    if (isOpen())
      throw std::runtime_error("Already open. Greed is bad.");

    SDL_AudioSpec desired = {};
    desired.freq = m_cfg.freq;
    desired.format = AUDIO_S16SYS;
    desired.channels = m_cfg.channels;
    desired.samples = m_cfg.samples;
    desired.callback = nullptr; // dequeue mode — callbacks are spooky

    m_device = SDL_OpenAudioDevice(
        device_name, /*iscapture=*/1, &desired, &m_obtained,
        SDL_AUDIO_ALLOW_FORMAT_CHANGE // driver picks the format, we adapt
    );

    if (m_device == 0)
      throw std::runtime_error(SDL_GetError());
  }

  void start() {
    assertOpen();
    m_pcm.clear();
    SDL_PauseAudioDevice(m_device, 0); // 0 = unpause = recording begins
    m_recording = true;
  }

  // Call this periodically (e.g. in your game loop or a polling thread)
  void poll() {
    if (!m_recording)
      return;

    uint32_t available = SDL_GetQueuedAudioSize(m_device);
    if (available == 0)
      return;

    size_t offset = m_pcm.size();
    m_pcm.resize(offset + available);
    SDL_DequeueAudio(m_device, m_pcm.data() + offset, available);
  }

  void stop() {
    assertOpen();
    SDL_PauseAudioDevice(m_device, 1); // 1 = pause = silence descends
    poll();                            // drain whatever's left in the queue
    m_recording = false;
  }

  void saveWAV(const std::string &path) const {
    if (m_pcm.empty())
      throw std::runtime_error("Nothing recorded. Awkward.");

    std::ofstream f(path, std::ios::binary);
    if (!f)
      throw std::runtime_error("Can't open file: " + path);

    WAVHeader hdr = makeHeader();
    f.write(reinterpret_cast<const char *>(&hdr), sizeof(hdr));
    f.write(reinterpret_cast<const char *>(m_pcm.data()), m_pcm.size());
  }

  // Utility: list available capture devices
  static void listDevices() {
    int count = SDL_GetNumAudioDevices(/*iscapture=*/1);
    SDL_Log("Capture devices (%d):", count);
    for (int i = 0; i < count; ++i)
      SDL_Log("  [%d] %s", i, SDL_GetAudioDeviceName(i, 1));
  }

  bool isOpen() const { return m_device != 0; }
  bool isRecording() const { return m_recording; }
  size_t bytesRecorded() const { return m_pcm.size(); }
  SDL_AudioSpec spec() const { return m_obtained; }

private:
  // The ancient WAV ritual. Do not question it.
  struct __attribute__((packed)) WAVHeader {
    char riff_id[4] = {'R', 'I', 'F', 'F'};
    uint32_t riff_size = 0;
    char wave_id[4] = {'W', 'A', 'V', 'E'};
    char fmt_id[4] = {'f', 'm', 't', ' '};
    uint32_t fmt_size = 16;
    uint16_t audio_format = 1; // PCM. We are not fancy.
    uint16_t num_channels = 0;
    uint32_t sample_rate = 0;
    uint32_t byte_rate = 0;
    uint16_t block_align = 0;
    uint16_t bits_per_sample = 0;
    char data_id[4] = {'d', 'a', 't', 'a'};
    uint32_t data_size = 0;
  };

  WAVHeader makeHeader() const {
    uint16_t bps = SDL_AUDIO_BITSIZE(m_obtained.format);
    uint16_t channels = m_obtained.channels;
    uint32_t sr = m_obtained.freq;

    WAVHeader h;
    h.num_channels = channels;
    h.sample_rate = sr;
    h.bits_per_sample = bps;
    h.block_align = channels * (bps / 8);
    h.byte_rate = sr * h.block_align;
    h.data_size = static_cast<uint32_t>(m_pcm.size());
    h.riff_size = 36 + h.data_size;
    return h;
  }

  void assertOpen() const {
    if (!isOpen())
      throw std::runtime_error("Device not open. Call open() first.");
  }

  Config m_cfg;
  SDL_AudioDeviceID m_device = 0;
  SDL_AudioSpec m_obtained = {};
  std::vector<uint8_t> m_pcm;
  bool m_recording = false;
};

} // namespace tebya