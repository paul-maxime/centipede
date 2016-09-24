#include "Player.hpp"
#include "Field.hpp"
#include "Missile.hpp"
#include "Resources.hpp"
#include "GameScene.hpp"
#include "MathHelper.hpp"

Player::Player(GameScene& game)
  : AEntity(game),
    m_reload(0.0f)
{
  m_sprite.setTexture(Resources::getInstance().getTexture("player.png"));
  setBounds(true);
}

Player::~Player()
{
}

void Player::fire()
{
  if (m_reload <= 0.0f)
    {
      Resources::getInstance().getSound("shot.wav").play();
      field().addEntity(new Missile(*this));
      m_reload = 0.2f;
    }
}

void Player::kill()
{
  field().setPlayerKilled();
}

void Player::update()
{
  if (m_reload > 0.0f)
    m_reload -= 1.0f / 60.0f;

  sf::Vector2f direction;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    direction += sf::Vector2f(-1.0f, 0.0f);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    direction += sf::Vector2f(1.0f, 0.0f);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    direction += sf::Vector2f(0.0f, -1.0f);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    direction += sf::Vector2f(0.0f, 1.0f);
  direction = MathHelper::normalize(direction);
  direction *= 15.0f / 60.0f;
  move(direction.x, direction.y);

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    fire();
}

void Player::draw(sf::RenderWindow& window)
{
  m_sprite.setPosition(static_cast<int>(getX() * 32),
		       static_cast<int>(getY() * 32));
  m_sprite.setColor(game().entitiesColor());
  window.draw(m_sprite);
}
