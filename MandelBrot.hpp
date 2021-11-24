#pragma once

#include <complex>
#include <chrono>
#include <iostream>

#include <SFML/Graphics.hpp>

class Mandelbrot
{
public:
  Mandelbrot(const unsigned int, const unsigned int, const unsigned int, std::pair<double, double>, std::pair<double, double>);

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
  bool isMouseInWindow(const sf::Vector2i);
  void updatePanning(const sf::Vector2i &mousePos);
  const unsigned int windowXSize;
  const unsigned int windowYSize;
  const unsigned int n_max;
  std::pair<double, double> xRange = { -2.0f, 2.0f };
  std::pair<double, double> yRange = { -2.0f, 2.0f };
  sf::View view;
  sf::Image drawImage = {};
  sf::Texture drawTexture = {};
  sf::Sprite drawSprite = {};
  bool updateTime = { true };
  const float MOVE_SPEED_FACTOR = { 0.001f };
  const float EDGE_PANE = { 0.15f };
  void setXrangeAbsolute(std::pair<double, double> newVal);
  void setYrangeAbsolute(std::pair<double, double> newVal);
  void setXrangeRelative(double ratio);
  void setYrangeRelative(double ratio);
  sf::Vector2f refreshSize = {};
  sf::Vector2f refreshPosition = {};
  sf::Color colorToHSV(int, float, float);
};
