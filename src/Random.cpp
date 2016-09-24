#include <cstdlib>
#include <ctime>
#include "Random.hpp"

void Random::init()
{
  std::srand(std::time(0));
}

int Random::nextInt(int max)
{
  return std::rand() % max;
}
