#include "Missile.hpp"
#include "Player.hpp"
#include "Field.hpp"
#include "GameScene.hpp"
#include "Resources.hpp"
#include "Scorpion.hpp"
#include "Flea.hpp"
#include "Spider.hpp"

Missile::Missile(Player& player)
  : AEntity(player.game())
{
  m_sprite.setTexture(Resources::getInstance().getTexture("missile.png"));
  setPosition(player.getX() + 0.45f, player.getY() - 0.5f);
  checkCollision();
}

Missile::~Missile()
{
}

void Missile::update()
{
  move(0.0f, -45.0f / 60.0f);
  if (getY() < -1.0f)
    {
      field().removeEntity(this);
      return;
    }
  checkCollision();
}

void Missile::draw(sf::RenderWindow& window)
{
  m_sprite.setPosition(static_cast<int>(getX() * 32),
		       static_cast<int>(getY() * 32));
  window.draw(m_sprite);
}

void Missile::checkCollision()
{
  int x = static_cast<int>(getX());
  int y = static_cast<int>(getY());
  if (x >= 0 && y >= 0)
    {
      Field::Mushroom& mushroom = field().getMushroomAt(x, y);
      if (mushroom.life > 0)
	{
	  Resources::getInstance().getSound("pop2.wav").play();
	  if (--mushroom.life == 0)
	    {
	      mushroom.is_infected = false;
	      game().addScore(1);
	    }
	  field().removeEntity(this);
	  return;
	}
    }
  std::vector<AEntity*>& entities = field().entities();
  for (std::vector<AEntity*>::iterator it = entities.begin();
       it != entities.end();
       ++it)
    {
      AEntity* entity = *it;
      Centipede* centipede = 0;
      if ((centipede = dynamic_cast<Centipede*>(entity)) ||
	  dynamic_cast<Scorpion*>(entity) ||
	  dynamic_cast<Flea*>(entity) ||
	  dynamic_cast<Spider*>(entity))
	{
	  if ((static_cast<int>(entity->getX()) == static_cast<int>(getX()) &&
	       static_cast<int>(entity->getY()) == static_cast<int>(getY())) ||
	      (static_cast<int>(entity->getX() + 0.5f) == static_cast<int>(getX()) &&
	       static_cast<int>(entity->getY() + 0.5f) == static_cast<int>(getY())))
	    {
	      Resources::getInstance().getSound("pop1.wav").play();
	      if (centipede)
		{
		  centipede->kill();
		  game().addScore(centipede->isHead() ? 100 : 10);
		}
	      else
		{
		  game().addScore(100);
		  field().removeEntity(entity);
		}
	      field().removeEntity(this);
	      return;
	    }
	}
    }
}
