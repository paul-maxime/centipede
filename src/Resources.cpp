#include <stdexcept>
#include "Resources.hpp"

Resources* Resources::m_instance;

void Resources::init()
{
  m_instance = new Resources();
}

Resources& Resources::getInstance()
{
  return *m_instance;
}

sf::Texture& Resources::getTexture(const std::string& name)
{
  std::map<std::string, sf::Texture>::iterator it = m_textures.find(name);
  if (it == m_textures.end())
    throw std::runtime_error("Could not get texture " + name + ".");
  return it->second;
}

sf::Sound& Resources::getSound(const std::string& name)
{
  std::map<std::string, sf::Sound>::iterator it = m_sounds.find(name);
  if (it == m_sounds.end())
    throw std::runtime_error("Could not get sound " + name + ".");
  return it->second;
}

sf::Music& Resources::getMusic(const std::string& name)
{
  std::map<std::string, sf::Music*>::iterator it = m_musics.find(name);
  if (it == m_musics.end())
    throw std::runtime_error("Could not get music " + name + ".");
  return *(it->second);
}

sf::Font& Resources::getFont(const std::string& name)
{
  std::map<std::string, sf::Font>::iterator it = m_fonts.find(name);
  if (it == m_fonts.end())
    throw std::runtime_error("Could not get font " + name + ".");
  return it->second;
}

Resources::Resources()
{
  loadTexture("mush01.png");
  loadTexture("mush02.png");
  loadTexture("mush03.png");
  loadTexture("mush04.png");
  loadTexture("player.png");
  loadTexture("missile.png");
  loadTexture("centi-head.png");
  loadTexture("centi-body.png");
  loadTexture("scorpion.png");
  loadTexture("spider.png");

  loadSound("shot.wav");
  loadSound("pop1.wav");
  loadSound("pop2.wav");
  loadSound("explosion.ogg");
  loadMusic("music.ogg");

  loadFont("future.ttf");
}

Resources::~Resources()
{
}

void Resources::loadTexture(const std::string& filename)
{
  if (!m_textures[filename].loadFromFile("assets/" + filename))
    throw std::runtime_error("Could not load texture assets/" + filename + ".");
}

void Resources::loadSound(const std::string& filename)
{
  if (!m_soundbuffers[filename].loadFromFile("assets/" + filename))
    throw std::runtime_error("Could not load sound assets/" + filename + ".");
  m_sounds[filename].setBuffer(m_soundbuffers[filename]);
}

void Resources::loadMusic(const std::string& filename)
{
  sf::Music* music = new sf::Music();
  if (!music->openFromFile("assets/" + filename))
    {
      delete music;
      throw std::runtime_error("Could not open music assets/" + filename + ".");
    }
  m_musics[filename] = music;
}

void Resources::loadFont(const std::string& filename)
{
  if (!m_fonts[filename].loadFromFile("assets/" + filename))
    throw std::runtime_error("Could not load font assets/" + filename + ".");
}
