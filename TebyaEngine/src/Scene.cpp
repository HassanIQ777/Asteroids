#pragma once

#include "Tebya/Scene.hpp"
#include <algorithm>

namespace tebya {

template <typename T, typename... Args>
T *Scene::add(const std::string &name, Args &&...args) {
  auto widget = std::make_unique<T>(std::forward<Args>(args)...);
  T *raw = widget.get(); // grab raw ptr before we move it
  widgets.emplace_back(name, std::move(widget));
  return raw; // caller can keep this for quick access
}

Widget *Scene::get(const std::string &name) {
  for (auto &[n, w] : widgets)
    if (n == name)
      return w.get();
  return nullptr;
}

// Typed get — returns nullptr if wrong type
template <typename T> T *Scene::get(const std::string &name) {
  return dynamic_cast<T *>(get(name));
}

void Scene::update() {
  for (auto &[name, w] : widgets)
    if (w->getVisibility())
      w->update();
}

void Scene::render() {
  for (auto &[name, w] : widgets)
    if (w->getVisibility())
      w->render();
}

void Scene::remove(const std::string &name) {
  widgets.erase(
      std::remove_if(widgets.begin(), widgets.end(),
                     [&](const auto &pair) { return pair.first == name; }),
      widgets.end());
}

} // namespace tebya