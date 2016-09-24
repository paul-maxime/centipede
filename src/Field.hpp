#pragma once

#include <vector>
#include "AEntity.hpp"
#include "Player.hpp"
#include "Centipede.hpp"

class GameScene;

class Field
{
public:
  struct Mushroom
  {
    unsigned int life;
    bool is_infected;
  };

private:
  GameScene& m_game;
  Mushroom* m_mushrooms;
  sf::Texture **m_mushroomTexture;
  sf::Sprite m_mushroomSprite;
  int* m_collisions;
  std::vector<AEntity*> m_entities;
  std::vector<AEntity*> m_oldentities;
  std::vector<AEntity*> m_newentities;
  Player* m_player;
  int m_width;
  int m_height;
  int m_bottom;

  int m_snakeSize;
  float m_snakeSpeed;

  bool m_emptyMap;
  bool m_atBottom;
  bool m_playerKilled;
  bool m_gameOverState;
  int m_gameOverTick;

public:
  Field(GameScene& game, int width, int height);
  virtual ~Field();

  Player& player();
  std::vector<AEntity*>& entities();

  int width() const;
  int height() const;
  int bottom() const;
  bool wasMapCleared() const;
  void setAtBottom();
  void setPlayerKilled();

  void addEntity(AEntity* entity);
  void removeEntity(AEntity* entity);
  void clearEntities();

  Mushroom& getMushroomAt(int x, int y) const;
  void addMushroomAt(int x, int y, bool infected);

  bool isCollisionAt(int x, int y);

  void update();
  void draw(sf::RenderWindow& window);

  void spawnSnake(int size, float speed, bool side);

private:
  void init();
  void initRandomMushrooms();
  void initNewPlayer();
  void clearAll();

  void newRound();

  bool repareMushroom();

  void cleanEntities();
  void internalRemoveEntity(AEntity* entity);

  void calculateCollisionMap();
};
