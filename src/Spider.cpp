#include "Spider.hpp"
#include "Resources.hpp"
#include "Field.hpp"
#include "GameScene.hpp"
#include "Random.hpp"

Spider::Spider(GameScene& game, int y, int direction)
  : AEntity(game),
    m_direction(direction)
{
  m_sprite.setTexture(Resources::getInstance().getTexture("spider.png"));
  setPosition(direction == -1 ? field().width() : -1, y);
}

Spider::~Spider()
{
}

void Spider::update()
{
  move((5.0f / 60.0f) * static_cast<float>(m_direction), 0.0f);
  if (getY() > field().height() + 2)
    {
      field().removeEntity(this);
      return;
    }
  eatRandomMush();
  checkCollision();
}

void Spider::draw(sf::RenderWindow& window)
{
  m_sprite.setPosition(static_cast<int>(getX() * 32),
		       static_cast<int>(getY() * 32));
  m_sprite.setColor(game().entitiesColor());
  window.draw(m_sprite);
}

void Spider::eatRandomMush()
{
  if (Random::nextInt(40) != 0) return;

  int x = static_cast<int>(getX());
  int y = static_cast<int>(getY());
  if (x >= 0 && y >= 0 && x < field().width() && y < field().height())
    {
      Field::Mushroom& mush = field().getMushroomAt(x, y);
      if (mush.life)
	{
	  mush.life = 0;
	  mush.is_infected = false;
	}
    }
}

void Spider::checkCollision()
{
  Player& player = field().player();

  if (static_cast<int>(getX() + 0.5f) == static_cast<int>(player.getX() + 0.5) &&
      static_cast<int>(getY() + 0.5f) == static_cast<int>(player.getY() + 0.5))
    {
      player.kill();
    }
}
