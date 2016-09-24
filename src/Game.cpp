#include <stdexcept>
#include "Game.hpp"
#include "MenuScene.hpp"

Game::Game()
{
  m_window.create(sf::VideoMode(32 * 32, 24 * 32), "Centipede");
  m_scenes.open(new MenuScene(m_scenes));
}

Game::~Game()
{
}

void Game::run()
{
  sf::Clock clock;
  float seconds = 0.0f;
  while (m_window.isOpen())
    {
      if (!m_scenes.isEmpty())
	{
	  seconds += clock.restart().asSeconds();
	  handleEvents();
	  while (seconds > (1.0f / 60.0f))
	    {
	      update();
	      seconds -= (1.0f / 60.0f);
	    }
	  draw();
	  sf::sleep(sf::milliseconds(1));
	}
      else
	m_window.close();
    }
}

void Game::handleEvents()
{
  sf::Event event;
  while (m_window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
	m_window.close();
      m_scenes.handleEvent(event);
    }
}

void Game::update()
{
  m_scenes.update();
}

void Game::draw()
{
  m_window.clear();
  m_scenes.draw(m_window);
  m_window.display();
}
