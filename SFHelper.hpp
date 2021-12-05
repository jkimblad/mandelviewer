#include <SFML/Graphics.hpp>

namespace sfh {

void setPixelWithBoundsCheck(sf::Image &image, unsigned int x, unsigned int y, sf::Color &color)
{
  sf::Vector2u imgSize = image.getSize();
  if (x > imgSize.x || y > imgSize.y) {
    throw std::runtime_error("Setting pixel out of bounds of picture!");
  } else {
    image.setPixel(x, y, color);
  }
}

// hue: 0-360°; sat: 0.f-1.f; val: 0.f-1.f
sf::Color hSVToColor(int hue, float sat, float val)
{
  hue %= 360;
  while (hue < 0) hue += 360;

  if (sat < 0.f) sat = 0.f;
  if (sat > 1.f) sat = 1.f;

  if (val < 0.f) val = 0.f;
  if (val > 1.f) val = 1.f;

  int h = hue / 60;
  float f = static_cast<float>(hue) / 60 - static_cast<float>(h);
  float p = val * (1.f - sat);
  float q = val * (1.f - sat * f);
  float t = val * (1.f - sat * (1 - f));

  sf::Uint8 uVal = static_cast<sf::Uint8>(val * 255);
  sf::Uint8 uT = static_cast<sf::Uint8>(t * 255);
  sf::Uint8 uP = static_cast<sf::Uint8>(p * 255);
  sf::Uint8 uQ = static_cast<sf::Uint8>(q * 255);


  switch (h) {
  default:
  case 0:
  case 6:
    return sf::Color(uVal, uT, uP);
  case 1:
    return sf::Color(uQ, uVal, uP);
  case 2:
    return sf::Color(uP, uVal, uT);
  case 3:
    return sf::Color(uP, uQ, uVal);
  case 4:
    return sf::Color(uT, uP, uVal);
  case 5:
    return sf::Color(uVal, uP, uQ);
  }
}

}// namespace sfh