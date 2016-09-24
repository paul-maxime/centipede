#include <cmath>
#include "MathHelper.hpp"

sf::Vector2f MathHelper::normalize(const sf::Vector2f& source)
{
  float length = std::sqrt((source.x * source.x) + (source.y * source.y));
  if (length != 0)
    return sf::Vector2f(source.x / length, source.y / length);
  return source;
}
