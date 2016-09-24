#include <algorithm>
#include <stdexcept>
#include "ScenesContainer.hpp"

ScenesContainer::ScenesContainer()
{
}

ScenesContainer::~ScenesContainer()
{
  for (std::list<IDrawable*>::iterator it = m_scenes.begin();
       it != m_scenes.end();
       ++it)
    {
      delete *it;
    }
}

void ScenesContainer::open(IDrawable* scene)
{
  m_newscenes.push_back(scene);
}

void ScenesContainer::close(IDrawable* scene)
{
  m_oldscenes.push_back(scene);
}

bool ScenesContainer::isEmpty() const
{
  return (m_newscenes.size() == 0 && m_oldscenes.size() == 0 && m_scenes.size() == 0);
}

void ScenesContainer::handleEvent(const sf::Event& event)
{
  if (m_scenes.size() != 0)
    m_scenes.front()->handleEvent(event);
}

void ScenesContainer::update()
{
  if (m_scenes.size() != 0)
    m_scenes.front()->update();
  clean();
}

void ScenesContainer::draw(sf::RenderWindow& window)
{
  for (std::list<IDrawable*>::reverse_iterator it = m_scenes.rbegin();
       it != m_scenes.rend();
       ++it)
    {
      (*it)->draw(window);
    }
}

void ScenesContainer::clean()
{
  for (std::list<IDrawable*>::iterator it = m_newscenes.begin();
       it != m_newscenes.end();
       ++it)
    {
      m_scenes.push_front(*it);
    }
  m_newscenes.clear();
  for (std::list<IDrawable*>::iterator it = m_oldscenes.begin();
       it != m_oldscenes.end();
       ++it)
    {
      internalClose(*it);
    }
  m_oldscenes.clear();
}

void ScenesContainer::internalClose(IDrawable* scene)
{
  std::list<IDrawable*>::iterator it = std::find(m_scenes.begin(), m_scenes.end(), scene);
  if (it == m_scenes.end())
    throw std::runtime_error("Tried to close a non-opened scene.");
  m_scenes.erase(it);
  delete scene;
}
