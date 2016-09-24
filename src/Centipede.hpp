#pragma once

#include "AEntity.hpp"

class Centipede : public AEntity
{
public:
  enum { UP, LEFT, DOWN, RIGHT };

private:
  sf::Sprite m_sprite;
  Centipede* m_parent;
  Centipede* m_son;
  int m_oldDirection;
  int m_direction;
  int m_oldPosition;
  int m_vertical;
  float m_speed;
  bool m_isHead;
  bool m_downForEver;

public:
  Centipede(GameScene& game, Centipede* parent, int x, int y, float speed);
  virtual ~Centipede();

  void setHead(bool value);
  bool isHead() const;
  int direction() const;
  void direction(int direction);

  void kill();

  virtual void update();
  virtual void draw(sf::RenderWindow& window);

private:
  void applyMovement();
  void checkHead();
  void checkCollision();
};
