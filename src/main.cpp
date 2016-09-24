#include <iostream>
#include "Random.hpp"
#include "Resources.hpp"
#include "Game.hpp"

int main()
{
  try
    {
      Random::init();
      Resources::init();
      Game game;
      game.run();
      return EXIT_SUCCESS;
    }
  catch (const std::exception& e)
    {
      std::cerr << e.what() << std::endl;
      return EXIT_FAILURE;
    }
}
