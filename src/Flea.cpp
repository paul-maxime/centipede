#include "Flea.hpp"
#include "Resources.hpp"
#include "Field.hpp"
#include "GameScene.hpp"
#include "Random.hpp"

Flea::Flea(GameScene& game, int x)
  : AEntity(game)
{
  m_sprite.setTexture(Resources::getInstance().getTexture("scorpion.png"));
  setPosition(x, -1);
}

Flea::~Flea()
{
}

void Flea::update()
{
  move(0.0f, 10.0f / 60.0f);
  if (getY() > field().height() + 2)
    {
      field().removeEntity(this);
      return;
    }
  spawnRandomMush();
  checkCollision();
}

void Flea::draw(sf::RenderWindow& window)
{
  m_sprite.setPosition(static_cast<int>(getX() * 32),
		       static_cast<int>(getY() * 32));
  m_sprite.setColor(game().entitiesColor());
  window.draw(m_sprite);
}

void Flea::spawnRandomMush()
{
  if (Random::nextInt(20) != 0) return;

  int x = static_cast<int>(getX());
  int y = static_cast<int>(getY());
  if (x >= 0 && y > 0 && x < field().width() && y < field().height())
    {
      Field::Mushroom& mush = field().getMushroomAt(x, y);
      if (!mush.life)
	mush.life = 4;
    }
}

void Flea::checkCollision()
{
  Player& player = field().player();

  if (static_cast<int>(getX() + 0.5f) == static_cast<int>(player.getX() + 0.5) &&
      static_cast<int>(getY() + 0.5f) == static_cast<int>(player.getY() + 0.5))
    {
      player.kill();
    }
}
