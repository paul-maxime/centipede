#pragma once

#include "AEntity.hpp"

class Flea : public AEntity
{
private:
  sf::Sprite m_sprite;

public:
  Flea(GameScene& game, int x);
  virtual ~Flea();

  virtual void update();
  virtual void draw(sf::RenderWindow& window);

private:
  void spawnRandomMush();
  void checkCollision();
};
