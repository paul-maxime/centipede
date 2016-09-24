#pragma once

#include "IDrawable.hpp"
#include "ScenesContainer.hpp"

class MenuScene : public IDrawable
{
private:
  ScenesContainer& m_container;
  sf::Text m_titleText;
  sf::Text m_playText;
  sf::Clock m_clock;
  int m_time;

public:
  MenuScene(ScenesContainer& container);
  virtual ~MenuScene();

  virtual void handleEvent(const sf::Event& event);
  virtual void update();
  virtual void draw(sf::RenderWindow& window);
};
