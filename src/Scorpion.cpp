#include "Scorpion.hpp"
#include "Resources.hpp"
#include "Field.hpp"
#include "GameScene.hpp"

Scorpion::Scorpion(GameScene& game, int y, int direction)
  : AEntity(game),
    m_direction(direction)
{
  m_sprite.setTexture(Resources::getInstance().getTexture("scorpion.png"));
  setPosition(direction == -1 ? field().width() : -1, y);
}

Scorpion::~Scorpion()
{
}

void Scorpion::update()
{
  move((10.0f / 60.0f) * static_cast<float>(m_direction), 0.0f);
  if (getX() < -2.0f || getX() > field().width() + 2)
    {
      field().removeEntity(this);
      return;
    }
  checkCollision();
}

void Scorpion::draw(sf::RenderWindow& window)
{
  m_sprite.setPosition(static_cast<int>(getX() * 32),
		       static_cast<int>(getY() * 32));
  m_sprite.setColor(game().entitiesColor());
  window.draw(m_sprite);
}

void Scorpion::checkCollision()
{
  int x = static_cast<int>(getX());
  int y = static_cast<int>(getY());
  if (x >= 0 && y >= 0 && x < field().width() && y < field().height())
    {
      Field::Mushroom& mush = field().getMushroomAt(x, y);
      if (mush.life)
	{
	  mush.is_infected = true;
	}
    }
}
