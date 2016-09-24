#pragma once

#include "AEntity.hpp"

class Player;

class Missile : public AEntity
{
private:
  sf::Sprite m_sprite;

public:
  Missile(Player& player);
  virtual ~Missile();

  virtual void update();
  virtual void draw(sf::RenderWindow& window);

private:
  void checkCollision();
};
