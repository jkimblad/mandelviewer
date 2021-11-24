#include "StatsBox.hpp"

StatsBox::StatsBox(float xPos, float yPos) : pos{ xPos, yPos }
{
  if (!textFont.loadFromFile(FONT_FILE)) {
    throw std::runtime_error("Failed to load font from file");
  }
}

void StatsBox::addStat(std::string key, std::string value)
{
  //TODO: check for uniquness in entries
  statsEntries.push_back(std::pair<std::string, std::string>(key, value));
}

void StatsBox::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
  float yOffset = 0;

  for (const auto &entry : statsEntries) {
    sf::Text text{ entry.first + ":\t" + entry.second, textFont };
    text.setPosition(sf::Vector2f{ pos.x, pos.y + yOffset });
    yOffset += static_cast<float>(FONT_SIZE + Y_OFFSET_GAP);
    target.draw(text, states);
  }
}

void StatsBox::setValue(const std::string &key, const std::string &val)
{
  for (auto &entry : statsEntries) {
    if (!entry.first.compare(key)) {
      entry.second = val;
      return;
    }
  }

  throw std::runtime_error("Could not find key " + key + " in stats entries!");
}