#pragma once

#include "AEntity.hpp"

class Spider : public AEntity
{
private:
  sf::Sprite m_sprite;
  int m_direction;

public:
  Spider(GameScene& game, int y, int direction);
  virtual ~Spider();

  virtual void update();
  virtual void draw(sf::RenderWindow& window);

private:
  void eatRandomMush();
  void checkCollision();
};
