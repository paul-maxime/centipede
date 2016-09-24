#include <sstream>
#include "GameOverScene.hpp"
#include "MenuScene.hpp"
#include "Resources.hpp"

GameOverScene::GameOverScene(ScenesContainer& container, int score)
  : m_container(container)
{
  m_titleText.setString("Game Over");
  m_titleText.setFont(Resources::getInstance().getFont("future.ttf"));
  m_titleText.setCharacterSize(64);
  m_titleText.setPosition(200, 100);

  std::ostringstream oss;
  oss << "Your score: " << score;

  m_scoreText.setString(oss.str());
  m_scoreText.setFont(Resources::getInstance().getFont("future.ttf"));
  m_scoreText.setCharacterSize(24);
  m_scoreText.setPosition(256, 192);
}

GameOverScene::~GameOverScene()
{
}


void GameOverScene::handleEvent(const sf::Event& event)
{
  if (event.type == sf::Event::KeyReleased)
    {
      m_container.close(this);
      if (event.key.code != sf::Keyboard::Escape)
	m_container.open(new MenuScene(m_container));
    }
}

void GameOverScene::update()
{
}

void GameOverScene::draw(sf::RenderWindow& window)
{
  window.draw(m_titleText);
  window.draw(m_scoreText);
}
