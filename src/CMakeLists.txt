cmake_minimum_required(VERSION 2.8)
project(Centipede)

set(SRC ${SRC}
  main.cpp
  Field.cpp
  Field.hpp
  Game.cpp
  Game.hpp

  Random.cpp
  Random.hpp
  MathHelper.cpp
  MathHelper.hpp
  Resources.cpp
  Resources.hpp

  ScenesContainer.cpp
  ScenesContainer.hpp
  MenuScene.cpp
  MenuScene.hpp
  GameScene.cpp
  GameScene.hpp
  GameOverScene.cpp
  GameOverScene.hpp

  IDrawable.hpp
  AEntity.hpp
  AEntity.cpp
  Player.hpp
  Player.cpp
  Missile.hpp
  Missile.cpp
  Centipede.hpp
  Centipede.cpp
  Scorpion.hpp
  Scorpion.cpp
  Spider.hpp
  Spider.cpp
  Flea.hpp
  Flea.cpp
)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../bin)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_executable(Centipede ${SRC})
target_link_libraries(Centipede sfml-system sfml-window sfml-graphics sfml-audio)
include_directories(${SRC_DIR})
