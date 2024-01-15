#pragma once

#include <SFML/Graphics.hpp>

#include "SFHelper.hpp"

class Mandelbrot
{
public:
  // Constructor
  Mandelbrot(const unsigned int, const unsigned int, const unsigned int, const unsigned int, std::pair<double, double>, std::pair<double, double>);

  // Functions
  void runUpdate(const sf::Vector2i &);
  void updateImage();
  std::pair<double, double> getXRange() const;
  std::pair<double, double> getYRange() const;
  sf::View &getView();
  sf::Sprite &toSprite();
  void zoom(float);
  void resetView();
  void getMandelPoint(sf::Vector2f);


private:
  // Functions
  bool isMouseInWindow(const sf::Vector2i);
  void updatePanning(const sf::Vector2i &mousePos);
  sf::Color colorToHSV(int, float, float);
  void mandelWorker(const sf::Vector2u, const sf::Vector2u);

  // Objects
  unsigned int windowXSize;
  unsigned int windowYSize;
  unsigned int n_max;
  unsigned int noThreads = 1;
  std::pair<double, double> xRange = { -2.0f, 2.0f };
  std::pair<double, double> yRange = { -2.0f, 2.0f };
  sf::View view;
  sf::Image drawImage = {};
  sf::Texture drawTexture = {};
  sf::Sprite drawSprite = {};
  bool updateTime = { true };
  float MOVE_SPEED_FACTOR = { 0.001f };
  float EDGE_PANE = { 0.15f };
  sf::Vector2f refreshSize = {};
  sf::Vector2f refreshPosition = {};
};
