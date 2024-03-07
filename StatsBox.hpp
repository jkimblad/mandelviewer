#pragma once

#include <string>
#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>

class StatsBox : public sf::Drawable
{
public:
  // Functions
  /*!
   * \brief Constructor.
   *
   * \param xPos Specifies the top-left corners position.
   * \param yPos Specifies the top-left corners position.
   */
  StatsBox(float, float);
  /*!
   * \brief Adds a stat consisting of a name/key and its value to be rendered in the StatsBox.
   *
   * \param key The key or the name of the value to be displayed.
   * \param value The corresponding value to be displayed.
   */
  void addStat(std::string, std::string);
  /*!
   * \brief Set or update the value for a given key.
   *
   * \param key The key or the name of the value to be set/updated.
   * \param val The value to be set/updated.
   */
  void setValue(const std::string &, const std::string &);

private:
  // Objects
  int updateTime {0};
  std::vector<std::pair<std::string, std::string>> statsEntries {};
  double scaleFactor {1.0};
  sf::Font textFont {};
  unsigned int FONT_SIZE {24};
  sf::Vector2f pos {0.0f, 0.0f};
  std::string FONT_FILE {"/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf"};
  unsigned int Y_OFFSET_GAP {5};

  // Functions
  void draw(sf::RenderTarget &, sf::RenderStates) const;
};