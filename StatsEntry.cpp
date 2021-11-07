#include "StatsEntry.hpp"

StatsEntry::StatsEntry(const std::string key, const std::string value, const sf::Font font, unsigned int size) : key(key), text({ key + ":\t" + value }, font, size)
{
}

void StatsEntry::setValue(std::string value)
{
  text.setString(key + ":\t" + value);
}

void StatsEntry::deleteEntry()
{
  deleted = true;
}

void StatsEntry::setPosition(const sf::Vector2f pos)
{
  text.setPosition(pos);
}

const sf::Text &StatsEntry::getText() const
{
  return text;
}

bool StatsEntry::isDeleted() const
{
  return deleted;
}
