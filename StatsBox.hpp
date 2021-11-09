#pragma once

#include <string>
#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>

#include "StatsEntry.hpp"

class StatsBox : public sf::Drawable
{
public:
  // Functions
  StatsBox(float, float);
  std::shared_ptr<StatsEntry> addStat(std::string, std::string);
  void update();

private:
  // Objects
  int updateTime = 0;
  std::vector<std::shared_ptr<StatsEntry>> statsEntries = {};
  double scaleFactor = 1.0f;
  sf::Font textFont = {};
  const unsigned int FONT_SIZE = 24;
  sf::Vector2f pos = { 0.0f, 0.0f };
  const std::string FONT_FILE = { "/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf" };
  const unsigned int Y_OFFSET_GAP = { 5 };

  // Functions
  void draw(sf::RenderTarget &, sf::RenderStates) const;
};