#include "StatsBox.hpp"

StatsBox::StatsBox(float xPos, float yPos) : pos{ xPos, yPos }
{
  if (!textFont.loadFromFile(FONT_FILE)) {
    throw std::runtime_error("Failed to load font from file");
  }
}

// ISSUE: The return value always have to be caught as a reference to be usefull, use pointer instead?
StatsEntry &StatsBox::addStat(std::string key, std::string value)
{
  statsEntries.push_back(StatsEntry{ key, value, textFont, FONT_SIZE });
  return statsEntries.back();
}

void StatsBox::update()
{
  auto it = statsEntries.begin();
  float yOffset = 0;
  for (int i = 0; i < statsEntries.size(); ++i) {
    StatsEntry &stat = statsEntries.at(i);
    stat.setPosition(sf::Vector2f(pos.x, pos.y + yOffset));
    yOffset += FONT_SIZE + 5.0f;
  }
}

void StatsBox::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
  for (const auto &entry : statsEntries) {
    std::cout << "string_text: " << entry.text.getString().toAnsiString() << "\n";
    target.draw(entry.text, states);
  }

  return;
}