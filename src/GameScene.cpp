#include <sstream>
#include "GameScene.hpp"
#include "GameOverScene.hpp"
#include "MenuScene.hpp"
#include "Random.hpp"
#include "MathHelper.hpp"
#include "Missile.hpp"
#include "Resources.hpp"

GameScene::GameScene(ScenesContainer& container) :
  m_container(container),
  m_field(*this, 32, 24),
  m_lives(3),
  m_score(0)
{
  generateColors();
  m_scoreText.setFont(Resources::getInstance().getFont("future.ttf"));
  m_scoreText.setCharacterSize(32);
  m_scoreText.setPosition(3, -1);
  m_life.setTexture(Resources::getInstance().getTexture("player.png"));
  Resources::getInstance().getMusic("music.ogg").play();
}

GameScene::~GameScene()
{
}

Field& GameScene::field()
{
  return m_field;
}

void GameScene::addScore(int score)
{
  m_score += score;
}

bool GameScene::loseLife()
{
  return (m_lives-- >= 0);
}

const sf::Color& GameScene::entitiesColor() const
{
  return m_entitiesColor;
}

const sf::Color& GameScene::mushroomColor() const
{
  return m_mushroomColor;
}

const sf::Color& GameScene::infectedColor() const
{
  return m_infectedColor;
}

void GameScene::handleEvent(const sf::Event& event)
{
  if (event.type == sf::Event::KeyReleased &&
      event.key.code == sf::Keyboard::Escape)
    {
      Resources::getInstance().getMusic("music.ogg").stop();
      m_container.open(new MenuScene(m_container));
      m_container.close(this);
    }
}

void GameScene::update()
{
  if (m_lives < 0)
    {
      Resources::getInstance().getMusic("music.ogg").stop();
      m_container.open(new GameOverScene(m_container, m_score));
      m_container.close(this);
      return;
    }
  m_field.update();
  if (m_field.wasMapCleared())
    generateColors();
}

void GameScene::draw(sf::RenderWindow& window)
{
  m_field.draw(window);
  std::ostringstream oss;
  oss << m_score;
  m_scoreText.setString(oss.str());
  window.draw(m_scoreText);
  for (int i = 0; i < m_lives; ++i)
    {
      m_life.setPosition((m_field.width() - (i + 1)) * 32, 0);
      window.draw(m_life);
    }
}

void GameScene::generateColors()
{
  m_entitiesColor = generateBrightColor();
  m_mushroomColor = generateBrightColor();
  m_infectedColor = revertColor(m_mushroomColor);
}

sf::Color GameScene::generateBrightColor()
{
  int r, g, b;
  r = Random::nextInt(129);
  g = Random::nextInt(129);
  b = Random::nextInt(129);
  while (r + g + b > 256)
    {
      if (r > 0) --r;
      if (g > 0) --g;
      if (b > 0) --b;
    }
  while (r + g + b < 192)
    {
      if (r < 256) ++r;
      if (g < 256) ++g;
      if (b < 256) ++b;
    }
  if (r > 64) r *= 2;
  if (g > 64) g *= 2;
  if (b > 64) b *= 2;
  if (r > 255) r = 255;
  if (g > 255) g = 255;
  if (b > 255) b = 255;

  return sf::Color(r, g, b);
}

sf::Color GameScene::revertColor(const sf::Color& color)
{
  return sf::Color(255 - color.r, 255 - color.g, 255 - color.b);
}
