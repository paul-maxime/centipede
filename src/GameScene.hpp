#pragma once

#include <SFML/Graphics.hpp>
#include "IDrawable.hpp"
#include "Field.hpp"
#include "AEntity.hpp"
#include "ScenesContainer.hpp"

class GameScene : public IDrawable
{
private:
  ScenesContainer& m_container;
  Field m_field;
  sf::Color m_entitiesColor;
  sf::Color m_mushroomColor;
  sf::Color m_infectedColor;
  sf::Sprite m_life;
  sf::Text m_scoreText;
  int m_lives;
  int m_score;

public:
  GameScene(ScenesContainer& container);
  virtual ~GameScene();

  Field& field();
  void addScore(int score);
  bool loseLife();
  void generateColors();

  const sf::Color& entitiesColor() const;
  const sf::Color& mushroomColor() const;
  const sf::Color& infectedColor() const;

  virtual void handleEvent(const sf::Event& event);
  virtual void update();
  virtual void draw(sf::RenderWindow& window);

private:
  sf::Color generateBrightColor();
  sf::Color revertColor(const sf::Color& color);
};
