#include "MenuScene.hpp"
#include "GameScene.hpp"
#include "Resources.hpp"

MenuScene::MenuScene(ScenesContainer& container)
  : m_container(container),
    m_time(0)
{
  m_titleText.setString("Centipede");
  m_titleText.setFont(Resources::getInstance().getFont("future.ttf"));
  m_titleText.setCharacterSize(64);
  m_titleText.setPosition(200, 100);
  m_playText.setString("Press any key to start...");
  m_playText.setFont(Resources::getInstance().getFont("future.ttf"));
  m_playText.setCharacterSize(24);
  m_playText.setPosition(256, 192);
}

MenuScene::~MenuScene()
{
}


void MenuScene::handleEvent(const sf::Event& event)
{
  if (event.type == sf::Event::KeyReleased)
    {
      m_container.close(this);
      if (event.key.code != sf::Keyboard::Escape)
	m_container.open(new GameScene(m_container));
    }
}

void MenuScene::update()
{
  m_time += 1;
}

void MenuScene::draw(sf::RenderWindow& window)
{
  window.draw(m_titleText);
  if (m_time % 60 < 30)
    window.draw(m_playText);
}
