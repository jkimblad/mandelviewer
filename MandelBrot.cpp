#include "MandelBrot.hpp"

Mandelbrot::Mandelbrot(const unsigned int window_x_size, const unsigned int window_y_size, const unsigned int n_max) : window_x_size(window_x_size), window_y_size(window_y_size), n_max(n_max) {
    drawImage.create(window_x_size, window_y_size, sf::Color(0, 255, 0));
}

void Mandelbrot::runUpdate() {
    double x_step = (xRange.second - xRange.first) / window_x_size;    
    double y_step = (yRange.second - yRange.first) / window_y_size;

    for(int yPixel = 0; yPixel < window_y_size; ++yPixel) {
        for(int xPixel = 0; xPixel < window_x_size; ++xPixel) {
            double b = yRange.first + (yPixel * y_step);
            double a = xRange.first + (xPixel * x_step);
            std::complex<double> c = {a, b};
            std::complex<double> z = {0, 0};
            std::uint8_t n = 0;
            while (std::abs(z) < 2 && n < n_max) {
                z = std::pow(z, 2) + c;
                ++n;
            }
            sf::Color pixel_color = {(uint8_t)(n * (255 / n_max)), 0, 0};
            drawImage.setPixel(xPixel, yPixel, pixel_color);
        }
    }
}

std::pair<double, double> Mandelbrot::getXRange() const {
    return xRange;
}

std::pair<double, double> Mandelbrot::getYRange() const {
    return yRange;
}

void Mandelbrot::setXrangeAbsolute(std::pair<double, double> newVal) {
    xRange = newVal;
}

void Mandelbrot::setYrangeAbsolute(std::pair<double, double> newVal) {
    yRange = newVal;
}

void Mandelbrot::setXrangeRelative(double ratio) {
    xRange.first = xRange.first * ratio;
    xRange.second = xRange.second * ratio;
}

void Mandelbrot::setYrangeRelative(double ratio) {
    yRange.first = yRange.first * ratio;
    yRange.second = yRange.second * ratio;
}

sf::Sprite& Mandelbrot::toSprite() {
    drawTexture.loadFromImage(drawImage);
    drawSprite = sf::Sprite(drawTexture);
    return drawSprite;
}
