#include <algorithm>
#include <stdexcept>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include "Field.hpp"
#include "Random.hpp"
#include "GameScene.hpp"
#include "Resources.hpp"
#include "Scorpion.hpp"
#include "Spider.hpp"
#include "Flea.hpp"

Field::Field(GameScene& game, int width, int height)
  : m_game(game),
    m_mushrooms(0),
    m_collisions(0),
    m_player(0),
    m_width(width),
    m_height(height),
    m_bottom(height / 3),
    m_snakeSize(5),
    m_snakeSpeed(0.095f),
    m_playerKilled(false),
    m_gameOverState(false)
{
  m_mushrooms = new Mushroom[width * height];
  m_collisions = new int[width * height];

  m_mushroomTexture = new sf::Texture*[4];
  m_mushroomTexture[3] = &Resources::getInstance().getTexture("mush01.png");
  m_mushroomTexture[2] = &Resources::getInstance().getTexture("mush02.png");
  m_mushroomTexture[1] = &Resources::getInstance().getTexture("mush03.png");
  m_mushroomTexture[0] = &Resources::getInstance().getTexture("mush04.png");

  init();
}

Field::~Field()
{
  clearAll();
  delete[] m_mushrooms;
  delete[] m_collisions;
  delete[] m_mushroomTexture;
}

Player& Field::player()
{
  return *m_player;
}

std::vector<AEntity*>& Field::entities()
{
  return m_entities;
}

int Field::width() const
{
  return m_width;
}

int Field::height() const
{
  return m_height;
}

int Field::bottom() const
{
  return m_bottom;
}

bool Field::wasMapCleared() const
{
  return m_emptyMap;
}

void Field::setAtBottom()
{
  m_atBottom = true;
}

void Field::setPlayerKilled()
{
  m_playerKilled = true;
}

void Field::addEntity(AEntity* entity)
{
  m_newentities.push_back(entity);
}

void Field::removeEntity(AEntity* entity)
{
  m_oldentities.push_back(entity);
}

void Field::clearEntities()
{
  for (std::vector<AEntity*>::iterator it = m_entities.begin();
       it != m_entities.end();
       ++it)
    {
      delete *it;
    }
  m_entities.clear();
  for (std::vector<AEntity*>::iterator it = m_newentities.begin();
       it != m_newentities.end();
       ++it)
    {
      delete *it;
    }
  m_newentities.clear();
  m_oldentities.clear();
}

Field::Mushroom& Field::getMushroomAt(int x, int y) const
{
  if (x < 0 || y < 0 || x >= m_width || y >= m_height)
    throw std::runtime_error("Tried to get an out-of-bounds mushroom.");
  return m_mushrooms[y * m_width + x];
}

void Field::addMushroomAt(int x, int y, bool infected)
{
  if (x < 0 || y < 0 || x >= m_width || y >= m_height)
    throw std::runtime_error("Tried to add an out-of-bounds mushroom.");
  m_mushrooms[y * m_width + x].life = 4;
  m_mushrooms[y * m_width + x].is_infected = infected;
}

bool Field::isCollisionAt(int x, int y)
{
  if (x < 0 || y < 0 || x >= m_width || y >= m_height)
    throw std::runtime_error("Tried to get an out-of-bounds collision.");
  if (getMushroomAt(x, y).life)
    return true;
  if (m_collisions[y * m_width + x] >= 4)
    {
      m_collisions[y * m_width + x]--;
      return true;
    }
  return false;
}

void Field::update()
{
  if (m_gameOverState)
    {
      if (--m_gameOverTick <= 0)
	{
	  if (!repareMushroom())
	    {
	      m_gameOverState = false;
	      if (m_game.loseLife())
		{
		  Resources::getInstance().getMusic("music.ogg").play();
		  initNewPlayer();
		  m_game.generateColors();
		  newRound();
		}
	    }
	  else
	    m_gameOverTick = 10;
	}
      return;
    }

  calculateCollisionMap();
  for (std::vector<AEntity*>::iterator it = m_entities.begin();
       it != m_entities.end();
       ++it)
    {
      (*it)->update();
    }

  if (m_playerKilled)
    {
      Resources::getInstance().getMusic("music.ogg").stop();
      Resources::getInstance().getSound("explosion.ogg").play();
      m_playerKilled = false;
      m_gameOverState = true;
      m_gameOverTick = 90;
      clearEntities();
    }
  else if (m_emptyMap)
    newRound();
  else if (m_atBottom)
    {
      if (Random::nextInt(600) == 0)
	{
	  spawnSnake(Random::nextInt(4) + 1, m_snakeSpeed, true);
	}
    }

  if (Random::nextInt(1600) == 0)
    {
      Scorpion* scorpion = new Scorpion(m_game,
					Random::nextInt(m_height - m_bottom),
					Random::nextInt(2) == 1 ? 1 : -1);
      addEntity(scorpion);
    }
  if (Random::nextInt(1200) == 0)
    {
      Spider* spider = new Spider(m_game,
				  m_height - m_bottom + Random::nextInt(m_bottom),
				  Random::nextInt(2) == 1 ? 1 : -1);
      addEntity(spider);
    }
  if (Random::nextInt(1600) == 0)
    {
      addEntity(new Flea(m_game, Random::nextInt(m_width)));
    }

  cleanEntities();
}

void Field::draw(sf::RenderWindow& window)
{
  for (int x = 0; x < m_width; ++x)
    for (int y = 0; y < m_height; ++y)
      {
	Field::Mushroom& mushroom = getMushroomAt(x, y);
  	if (mushroom.life)
  	  {
	    sf::Texture* texture =
	      m_mushroomTexture[mushroom.life > 4 ? 3 : mushroom.life - 1];
	    m_mushroomSprite.setTexture(*texture);

	    m_mushroomSprite.setColor(mushroom.is_infected ?
				      m_game.infectedColor() :
				      m_game.mushroomColor());

  	    m_mushroomSprite.setPosition(x * 32, y * 32);
  	    window.draw(m_mushroomSprite);
  	  }
      }
  for (std::vector<AEntity*>::iterator it = m_entities.begin();
       it != m_entities.end();
       ++it)
    {
      (*it)->draw(window);
    }
}

void Field::spawnSnake(int size, float speed, bool side)
{
  if (side)
    {
      Centipede *last = 0;
      int y = (m_height - m_bottom) + Random::nextInt(m_bottom);
      if (!getMushroomAt(0, y).life)
	{
	  for (int i = 1; i < size + 1; ++i)
	    {
	      last = new Centipede(m_game, last, -i, y, speed);
	      last->direction(Centipede::RIGHT);
	      m_entities.push_back(last);
	    }
	}
    }
  else
    {
      Centipede *last = 0;
      for (int i = 1; i < size + 1; ++i)
	{
	  last = new Centipede(m_game, last, static_cast<int>(m_width / 2), -i, speed);
	  m_entities.push_back(last);
	}
    }
}

void Field::init()
{
  clearAll();

  initNewPlayer();
  initRandomMushrooms();

  newRound();
}

void Field::initRandomMushrooms()
{
  for (int x = 0; x < m_width; ++x)
    for (int y = 1; y < m_height - 1; ++y)
      {
	if (Random::nextInt(100) < 4)
	  addMushroomAt(x, y, false);
      }
}

void Field::initNewPlayer()
{
  m_player = new Player(m_game);
  m_player->setPosition(m_width / 2.0f, m_height - 1.0f);
  m_entities.push_back(m_player);
}

void Field::clearAll()
{
  std::memset(m_mushrooms, 0, sizeof(Mushroom) * m_width * m_height);
  clearEntities();
}

void Field::newRound()
{
  if (m_snakeSize < 100)
    m_snakeSize += Random::nextInt(3);
  if (m_snakeSpeed < 0.5f)
    m_snakeSpeed += static_cast<float>(Random::nextInt(3)) / 100.0f;
  m_atBottom = false;
  spawnSnake(m_snakeSize, m_snakeSpeed, false);
}

bool Field::repareMushroom()
{
  for (int x = 0; x < m_width; ++x)
    for (int y = 0; y < m_height; ++y)
      {
	Mushroom& mushroom = getMushroomAt(x, y);
	if ((mushroom.life > 0 && mushroom.life < 4) ||
	    mushroom.is_infected)
	  {
	    mushroom.life = 4;
	    mushroom.is_infected = false;
	    m_game.addScore(10);
	    Resources::getInstance().getSound("pop2.wav").play();
	    return true;
	  }
      }
  return false;
}

void Field::cleanEntities()
{
  for (std::vector<AEntity*>::iterator it = m_newentities.begin();
       it != m_newentities.end();
       ++it)
    {
      m_entities.push_back(*it);
    }
  m_newentities.clear();
  for (std::vector<AEntity*>::iterator it = m_oldentities.begin();
       it != m_oldentities.end();
       ++it)
    {
      internalRemoveEntity(*it);
    }
  m_oldentities.clear();
}

void Field::internalRemoveEntity(AEntity* entity)
{
  std::vector<AEntity*>::iterator it = std::find(m_entities.begin(), m_entities.end(), entity);
  if (it == m_entities.end())
    // throw std::runtime_error("Tried to remove a non-existing entity.");
    return;
  m_entities.erase(it);
  delete entity;
}

void Field::calculateCollisionMap()
{
  m_emptyMap = true;
  std::memset(m_collisions, 0, sizeof(int) * m_width * m_height);
  for (std::vector<AEntity*>::iterator it = m_entities.begin();
       it != m_entities.end();
       ++it)
    {
      AEntity* entity = *it;
      if (dynamic_cast<Centipede*>(entity))
	{
	  m_emptyMap = false;
	  int x = static_cast<int>(entity->getX());
	  int y = static_cast<int>(entity->getY());
	  if (x >= 0 && y >= 0 && x < m_width && y < m_height)
	    {
	      m_collisions[y * m_width + x]++;
	    }
	}
    }
}
