#pragma once

#include <string>
#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>

class StatsBox : public sf::Drawable
{
public:
  // Functions
  StatsBox(float, float);
  void addStat(std::string, std::string);
  void update();
  void setValue(const std::string&, const std::string&);

private:
  // Objects
  int updateTime = 0;
  std::vector<std::pair<std::string, std::string>> statsEntries = {};
  double scaleFactor = 1.0f;
  sf::Font textFont = {};
  unsigned int FONT_SIZE = 24;
  sf::Vector2f pos = { 0.0f, 0.0f };
  std::string FONT_FILE = { "/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf" };
  unsigned int Y_OFFSET_GAP = { 5 };

  // Functions
  void draw(sf::RenderTarget &, sf::RenderStates) const;
};