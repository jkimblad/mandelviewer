#pragma once

#include <complex>
#include <chrono>
#include <iostream>

#include <SFML/Graphics.hpp>

class Mandelbrot {
public:
    Mandelbrot(const unsigned int window_x_size, const unsigned int window_y_size, const unsigned int n_max);

    void runUpdate();

    std::pair<double, double> getXRange() const;

    std::pair<double, double> getYRange() const;

    void setXrangeAbsolute(std::pair<double, double> newVal);

    void setYrangeAbsolute(std::pair<double, double> newVal);

    void setXrangeRelative(double ratio);

    void setYrangeRelative(double ratio);

    sf::Sprite& toSprite();

private:
    std::pair<double, double> xRange = {-2.0f, 1.0f};
    std::pair<double, double> yRange = {-2.0f, 2.0f};
    const unsigned int window_x_size;
    const unsigned int window_y_size;
    const unsigned int n_max;
    sf::Image drawImage = {};
    sf::Texture drawTexture = {};
    sf::Sprite drawSprite = {};

};
