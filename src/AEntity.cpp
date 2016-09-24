#include "AEntity.hpp"
#include "GameScene.hpp"
#include "Field.hpp"

AEntity::AEntity(GameScene& game)
  : m_game(game),
    m_field(game.field()),
    m_x(0),
    m_y(0),
    m_bounds(false)
{
}

AEntity::~AEntity()
{
}

GameScene& AEntity::game()
{
  return m_game;
}

Field& AEntity::field()
{
  return m_field;
}

float AEntity::getX() const
{
  return m_x;
}

float AEntity::getY() const
{
  return m_y;
}

void AEntity::move(float x, float y)
{
  m_x += x;
  m_y += y;

  if (m_bounds)
    {
      if (m_x < 0)
	m_x = 0;
      if (m_x >= field().width() - 1)
	m_x = field().width() - 1;
      if (m_y < field().height() - field().bottom())
	m_y = field().height() - field().bottom();
      if (m_y >= field().height() - 1)
	m_y = field().height() - 1;
    }
}

void AEntity::setPosition(float x, float y)
{
  m_x = x;
  m_y = y;
}

void AEntity::setBounds(bool value)
{
  m_bounds = value;
}

void AEntity::handleEvent(const sf::Event&)
{
}
