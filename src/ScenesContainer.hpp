#pragma once

#include <list>
#include <SFML/Graphics.hpp>
#include "IDrawable.hpp"

class ScenesContainer : public IDrawable
{
private:
  std::list<IDrawable*> m_scenes;
  std::list<IDrawable*> m_newscenes;
  std::list<IDrawable*> m_oldscenes;

public:
  ScenesContainer();
  virtual ~ScenesContainer();

  void open(IDrawable* scene);
  void close(IDrawable* scene);
  bool isEmpty() const;

  virtual void handleEvent(const sf::Event& event);
  virtual void update();
  virtual void draw(sf::RenderWindow& window);

private:
  void clean();
  void internalClose(IDrawable* scene);
};
