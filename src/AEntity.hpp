#pragma once

#include "IDrawable.hpp"

class GameScene;
class Field;

class AEntity : public IDrawable
{
private:
  GameScene& m_game;
  Field& m_field;
  float m_x;
  float m_y;
  bool m_bounds;

public:
  AEntity(GameScene& game);
  virtual ~AEntity();

  GameScene& game();
  Field& field();
  float getX() const;
  float getY() const;
  void move(float x, float y);
  void setPosition(float x, float y);
  void setBounds(bool value);

  virtual void handleEvent(const sf::Event&);
};
