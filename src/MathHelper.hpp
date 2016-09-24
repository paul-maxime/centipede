#pragma once

#include <SFML/System.hpp>

class MathHelper
{
public:
  static sf::Vector2f normalize(const sf::Vector2f& source);
private:
  MathHelper();
};
