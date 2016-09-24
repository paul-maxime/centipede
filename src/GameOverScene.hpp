#pragma once

#include "IDrawable.hpp"
#include "ScenesContainer.hpp"

class GameOverScene : public IDrawable
{
private:
  ScenesContainer& m_container;
  sf::Text m_titleText;
  sf::Text m_scoreText;

public:
  GameOverScene(ScenesContainer& container, int score);
  virtual ~GameOverScene();

  virtual void handleEvent(const sf::Event& event);
  virtual void update();
  virtual void draw(sf::RenderWindow& window);
};
