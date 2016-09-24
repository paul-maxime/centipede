#pragma once

#include "AEntity.hpp"

class Player : public AEntity
{
private:
  sf::Sprite m_sprite;
  float m_reload;

public:
  Player(GameScene& game);
  virtual ~Player();

  void fire();
  void kill();

  virtual void update();
  virtual void draw(sf::RenderWindow& window);
};
