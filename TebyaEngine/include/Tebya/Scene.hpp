#pragma once

#include "Widget.hpp"
#include <memory>
#include <string>
#include <vector>

namespace tebya {

class Scene {
  std::vector<std::pair<std::string, std::unique_ptr<Widget>>> widgets;

public:
  // The dark magic: perfect forwarding factory
  // Usage: scene.add<Button>("play_btn", bounds, onClick);
  template <typename T, typename... Args>
  T *add(const std::string &name, Args &&...args);

  Widget *get(const std::string &name);

  // Typed get — returns nullptr if wrong type
  template <typename T> T *get(const std::string &name);

  void update();

  void render();

  void remove(const std::string &name);
};

} // namespace tebya