#include <cmath>
#include "Centipede.hpp"
#include "Field.hpp"
#include "GameScene.hpp"
#include "Resources.hpp"

Centipede::Centipede(GameScene& game, Centipede* parent, int x, int y, float speed)
  : AEntity(game),
    m_parent(parent),
    m_son(0),
    m_oldDirection(LEFT),
    m_direction(DOWN),
    m_oldPosition(y),
    m_vertical(DOWN),
    m_speed(speed),
    m_isHead(false),
    m_downForEver(false)
{
  setPosition(x, y);
  setHead(!parent);
  if (parent)
    parent->m_son = this;
}

Centipede::~Centipede()
{
}

void Centipede::setHead(bool value)
{
  m_isHead = value;
  if (m_isHead)
    m_sprite.setTexture(Resources::getInstance().getTexture("centi-head.png"));
  else
    m_sprite.setTexture(Resources::getInstance().getTexture("centi-body.png"));
}

bool Centipede::isHead() const
{
  return m_isHead;
}

int Centipede::direction() const
{
  return m_direction;
}

void Centipede::direction(int direction)
{
  m_direction = direction;
}

void Centipede::kill()
{
  int x = static_cast<int>(getX());
  int y = static_cast<int>(getY());
  if (x >= 0 && y >= 0)
    field().getMushroomAt(x, y).life = 4;
  if (m_son)
    m_son->m_parent = 0;
  if (m_parent)
    m_parent->m_son = 0;
  field().removeEntity(this);
}

void Centipede::update()
{
  applyMovement();
  checkHead();
  checkCollision();
}

void Centipede::draw(sf::RenderWindow& window)
{
  m_sprite.setPosition(sf::Vector2f());
  m_sprite.setRotation(0);
  m_sprite.setColor(game().entitiesColor());
  if (m_isHead)
    {
      switch (m_direction)
	{
	case Centipede::UP:
	  m_sprite.move(32, 0);
	  m_sprite.setRotation(90);
	  break;
	case Centipede::DOWN:
	  m_sprite.move(0, 32);
	  m_sprite.setRotation(-90);
	  break;
	case Centipede::RIGHT:
	  m_sprite.move(32, 32);
	  m_sprite.setRotation(180);
	  break;
	}
    }
  m_sprite.move(static_cast<int>(getX() * 32),
		static_cast<int>(getY() * 32));
  window.draw(m_sprite);
}

void Centipede::applyMovement()
{
  float speed = m_speed;
  if (m_parent && m_parent->m_direction == m_direction && (m_direction == LEFT || m_direction == RIGHT))
    {
      if (std::abs(static_cast<int>(getX()) - static_cast<int>(m_parent->getX())) > 1.07f)
	speed += 0.015f;
      else if (std::abs(static_cast<int>(getX()) - static_cast<int>(m_parent->getX())) < 0.93f)
	speed -= 0.015f;
    }
  switch (m_direction)
    {
    case UP:
      move(0, -speed);
      field().setAtBottom();
      if (static_cast<int>(getY()) <= m_oldPosition - 2)
	{
	  m_direction = (m_oldDirection == LEFT ? RIGHT : LEFT);
	  setPosition(static_cast<int>(getX()), static_cast<int>(getY()) + 1);
	  if (static_cast<int>(getY()) == field().height() - field().bottom())
	    m_vertical = DOWN;
	}
      break;
    case DOWN:
      move(0, speed);
      if (static_cast<int>(getY()) != m_oldPosition && getY() >= 0)
	{
	  setPosition(static_cast<int>(getX()), static_cast<int>(getY()));
	  if (static_cast<int>(getY()) == field().height() - 1)
	    m_vertical = UP;
	  if (m_downForEver || getY() < 1)
	    {
	      if (m_vertical == DOWN)
		m_oldPosition = static_cast<int>(getY());
	      else
		m_downForEver = false;
	    }
	  else
	    m_direction = (m_oldDirection == LEFT ? RIGHT : LEFT);
	}
      break;
    case LEFT:
      move(-speed, 0);
      if (getX() < 0 ||
	  field().isCollisionAt(static_cast<int>(getX()), static_cast<int>(getY())))
	{
	  if (m_vertical == DOWN &&
	      getX() >= 0 &&
	      field().getMushroomAt(static_cast<int>(getX()), static_cast<int>(getY())).is_infected)
	    m_downForEver = true;
	  setPosition(static_cast<int>(getX() + 1), static_cast<int>(getY()));
	  m_oldDirection = LEFT;
	  m_oldPosition = static_cast<int>(getY());
	  m_direction = m_vertical;
	}
      break;
    case RIGHT:
      move(speed, 0);
      if (getX() < 1) break;
      if (getX() >= field().width() - 1 ||
	  field().isCollisionAt(static_cast<int>(getX() + 1), static_cast<int>(getY())))
	{
	  if (m_vertical == DOWN &&
	      getX() >= 0 &&
	      getX() < field().width() - 1 &&
	      field().getMushroomAt(static_cast<int>(getX() + 1), static_cast<int>(getY())).is_infected)
	    m_downForEver = true;
	  setPosition(static_cast<int>(getX()), static_cast<int>(getY()));
	  m_oldDirection = RIGHT;
	  m_oldPosition = static_cast<int>(getY());
	  if (m_vertical == DOWN && m_oldPosition == field().height() - 1)
	    m_vertical = UP;
	  m_direction = m_vertical;
	}
      break;
    }
}

void Centipede::checkHead()
{
  if (!m_isHead)
    {
      if (!m_parent || std::abs(getX() - m_parent->getX()) > 2.f)
	setHead(true);
    }
  else
    {
      if (m_parent && std::abs(getX() - m_parent->getX()) < 1.5f)
	setHead(false);
    }
}

void Centipede::checkCollision()
{
  Player& player = field().player();

  if (static_cast<int>(getX() + 0.5f) == static_cast<int>(player.getX() + 0.5) &&
      static_cast<int>(getY() + 0.5f) == static_cast<int>(player.getY() + 0.5))
    {
      player.kill();
    }
}
