#pragma once

#include <map>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Resources
{
private:
  static Resources* m_instance;
  std::map<std::string, sf::Texture> m_textures;
  std::map<std::string, sf::SoundBuffer> m_soundbuffers;
  std::map<std::string, sf::Sound> m_sounds;
  std::map<std::string, sf::Music*> m_musics;
  std::map<std::string, sf::Font> m_fonts;

public:
  static void init();
  static Resources& getInstance();

  sf::Texture& getTexture(const std::string& name);
  sf::Sound& getSound(const std::string& name);
  sf::Music& getMusic(const std::string& name);
  sf::Font& getFont(const std::string& name);

private:
  Resources();
  virtual ~Resources();

  void loadTexture(const std::string& filename);
  void loadSound(const std::string& filename);
  void loadMusic(const std::string& filename);
  void loadFont(const std::string& filename);
};
