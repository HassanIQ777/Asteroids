/* Part of https://github.com/HassanIQ777/libutils */

#pragma once

#include <chrono>

namespace tebya {

class Timer // i think this is pretty clear so it doesn't need documentation lol
{
private:
  std::chrono::time_point<std::chrono::high_resolution_clock> p_start_time;
  double p_total_elapsed = 0.0; // keeps total elapsed time
  bool p_running = false;       // whether timer is running

public:
  Timer();
  Timer(const double &start_time);

  void pause();

  void resume();

  double elapsed() const;

  void reset();

  void restart();

private:
  void p_start();
};

} // namespace tebya