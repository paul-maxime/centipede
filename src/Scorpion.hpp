#pragma once

#include "AEntity.hpp"

class Scorpion : public AEntity
{
private:
  sf::Sprite m_sprite;
  int m_direction;

public:
  Scorpion(GameScene& game, int y, int direction);
  virtual ~Scorpion();

  virtual void update();
  virtual void draw(sf::RenderWindow& window);

private:
  void checkCollision();
};
