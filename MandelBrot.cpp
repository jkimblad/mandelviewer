#include "MandelBrot.hpp"

Mandelbrot::Mandelbrot(const unsigned int window_x_size_, const unsigned int window_y_size_, const unsigned int n_max_, std::pair<double, double> xRange_, std::pair<double, double> yRange_)
  : windowXSize(window_x_size_),
    windowYSize(window_y_size_),
    n_max(n_max_),
    xRange(xRange_),
    yRange(yRange_),
    view(sf::FloatRect(0.0f, 0.0f, static_cast<float>(window_x_size_), static_cast<float>(window_y_size_)))
{
  drawImage.create(windowXSize, windowYSize, sf::Color(0, 255, 0));
}

void Mandelbrot::runUpdate(const sf::Vector2i &mousePos)
{
  if (updateTime) {
    updateImage();
  }

  updatePanning(mousePos);
}

bool Mandelbrot::isMouseInWindow(const sf::Vector2i mousePos)
{
  if (static_cast<unsigned int>(mousePos.x) < windowXSize && mousePos.x > 0 && static_cast<unsigned int>(mousePos.y) < windowYSize && mousePos.y > 0) {
    return true;
  }

  return false;
}

void Mandelbrot::resetView()
{
  sf::Vector2f viewCenter = view.getCenter();
  sf::Vector2f viewSize = view.getSize();
  sf::Vector2f topLeft{ viewCenter.x - (viewSize.x / 2),
    viewCenter.y - (viewSize.y / 2) };
  sf::Vector2f bottomRight{ topLeft.x + viewSize.x, topLeft.y + viewSize.y };

  // first element is top left, second is bottom right
  std::pair<double, double> xRatio = { topLeft.x / static_cast<float>(windowXSize), bottomRight.x / static_cast<float>(windowXSize) };
  std::pair<double, double> yRatio = { topLeft.y / static_cast<float>(windowYSize), bottomRight.y / static_cast<float>(windowYSize) };

  xRange = {
    xRange.first + ((xRange.second - xRange.first) * xRatio.first), xRange.first + ((xRange.second - xRange.first) * xRatio.second)
  };
  yRange = {
    yRange.first + ((yRange.second - yRange.first) * yRatio.first), yRange.first + ((yRange.second - yRange.first) * yRatio.second)
  };

  view = sf::View(sf::FloatRect(0.0f, 0.0f, static_cast<float>(windowXSize), static_cast<float>(windowYSize)));

  updateTime = true;
}

void Mandelbrot::updatePanning(const sf::Vector2i &mousePos)
{
  // Move around the view. Maybe use keys instead?
  sf::Vector2<float> viewCenter = view.getCenter();

  const float moveSpeed = { view.getSize().x * MOVE_SPEED_FACTOR };

  if (mousePos.x < static_cast<int>(static_cast<float>(windowXSize) * EDGE_PANE) && isMouseInWindow(mousePos))
    viewCenter = sf::Vector2f(viewCenter.x - (moveSpeed), viewCenter.y);
  if (mousePos.x > static_cast<int>(static_cast<float>(windowXSize) * (1.0f - EDGE_PANE)) && isMouseInWindow(mousePos))
    viewCenter = sf::Vector2f(viewCenter.x + (moveSpeed), viewCenter.y);
  if (mousePos.y < static_cast<int>(static_cast<float>(windowYSize) * EDGE_PANE) && isMouseInWindow(mousePos))
    viewCenter = sf::Vector2f(viewCenter.x, viewCenter.y - (moveSpeed));
  if (mousePos.y > static_cast<int>(static_cast<float>(windowYSize) * (1.0f - EDGE_PANE)) && isMouseInWindow(mousePos))
    viewCenter = sf::Vector2f(viewCenter.x, viewCenter.y + (moveSpeed));

  view.setCenter(viewCenter);

  refreshPosition = view.getCenter();
}

void Mandelbrot::zoom(float zoomFactor)
{
  //zoom
  view.zoom(zoomFactor);
  refreshSize = view.getSize();
}

void Mandelbrot::updateImage()
{
  double x_step = (xRange.second - xRange.first) / windowXSize;
  double y_step = (yRange.second - yRange.first) / windowYSize;

  for (unsigned int yPixel = 0; yPixel < windowYSize; ++yPixel) {
    for (unsigned int xPixel = 0; xPixel < windowXSize; ++xPixel) {
      double b = yRange.first + (yPixel * y_step);
      double a = xRange.first + (xPixel * x_step);
      std::complex<double> c = { a, b };
      std::complex<double> z = { 0, 0 };
      std::uint8_t n = 0;
      while (std::abs(z) < 2 && n < n_max) {
        z = std::pow(z, 2) + c;
        ++n;
      }
      sf::Color pixel_color = { static_cast<uint8_t>(n * (255 / n_max)), 0, 0 };
      drawImage.setPixel(xPixel, yPixel, pixel_color);
    }
  }
  updateTime = false;
}

void Mandelbrot::setXrangeAbsolute(std::pair<double, double> newVal)
{
  xRange = newVal;
}

void Mandelbrot::setYrangeAbsolute(std::pair<double, double> newVal)
{
  yRange = newVal;
}

void Mandelbrot::setXrangeRelative(double ratio)
{
  xRange.first = xRange.first * ratio;
  xRange.second = xRange.second * ratio;
}

void Mandelbrot::setYrangeRelative(double ratio)
{
  yRange.first = yRange.first * ratio;
  yRange.second = yRange.second * ratio;
}

sf::Sprite &Mandelbrot::toSprite()
{
  drawTexture.loadFromImage(drawImage);
  drawSprite = sf::Sprite(drawTexture);
  return drawSprite;
}

sf::View &Mandelbrot::getView()
{
  return view;
}
