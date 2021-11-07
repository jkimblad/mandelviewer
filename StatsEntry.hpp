#pragma once

#include <string>

#include <SFML/Graphics.hpp>

// Forward declaration of StatsBox
class StatsBox;

class StatsEntry
{
public:
    // Functions
    StatsEntry(const std::string, const std::string, const sf::Font, unsigned int);
    void setValue(std::string);
    void deleteEntry();

private:
    // Friends
    friend StatsBox;
    // Functions
    void setPosition(const sf::Vector2f);
    const sf::Text &getText() const;
    void clearUpdatedFlag();
    bool isDeleted() const;
    // Objects
    const std::string key = {};
    sf::Text text = {};
    bool deleted = false;
};