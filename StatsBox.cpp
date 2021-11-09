#include "StatsBox.hpp"

StatsBox::StatsBox(float xPos, float yPos) : pos{ xPos, yPos }
{
  if (!textFont.loadFromFile(FONT_FILE)) {
    throw std::runtime_error("Failed to load font from file");
  }
}

std::shared_ptr<StatsEntry> StatsBox::addStat(std::string key, std::string value)
{
  std::shared_ptr<StatsEntry> statsEntry_sp = std::make_shared<StatsEntry, std::string &, std::string &, sf::Font &, const unsigned int &>(key, value, textFont, FONT_SIZE);
  statsEntries.push_back(statsEntry_sp);
  return statsEntries.back();
}

void StatsBox::update()
{
  unsigned int yOffset = 0;
  for (long unsigned int i = 0; i < statsEntries.size(); ++i) {
    std::shared_ptr<StatsEntry> stat = statsEntries.at(i);
    stat->setPosition(sf::Vector2f(pos.x, pos.y + static_cast<float>(yOffset)));
    yOffset += FONT_SIZE + Y_OFFSET_GAP;
  }
}

void StatsBox::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
  for (const auto &entry : statsEntries) {
    std::cout << "string_text: " << entry->text.getString().toAnsiString() << "\n";
    target.draw(entry->text, states);
  }

  return;
}