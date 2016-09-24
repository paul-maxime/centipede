#pragma once

#include <SFML/Graphics.hpp>
#include "ScenesContainer.hpp"

class Game
{
private:
  sf::RenderWindow m_window;
  ScenesContainer m_scenes;

public:
  Game();
  virtual ~Game();

  void run();

private:
  void handleEvents();
  void update();
  void draw();
};
