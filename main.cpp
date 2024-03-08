#include <iostream>

#include <SFML/Graphics.hpp>

#include "MandelBrot.cpp"
#include "StatsBox.cpp"


// TODO: multithread mandelbrot calculations, split screen into sections
// TODO: Only recalculate screen when zoom reaches THRESHHOLD. Display old calculations until the new one is fully ready.

namespace Constants {
  constexpr int WINDOW_X_SIZE {1920};
  constexpr int WINDOW_Y_SIZE {1080};
  constexpr int N_MAX {125};
  constexpr int THREAD_COUNT {4};
  constexpr float EDGE_PANE {0.15f};
}

int main(int, char *[])
{
  //ContextSettings (unsigned int depth=0, unsigned int stencil=0, unsigned int antialiasing=0, unsigned int major=1, unsigned int minor=1, unsigned int attributes=Default, bool sRgb=false)
  sf::RenderWindow window(sf::VideoMode(Constants::WINDOW_X_SIZE, Constants::WINDOW_Y_SIZE), "Mandelbrot");
  sf::View guiView{ sf::FloatRect(0.0f, -1.0f * static_cast<float>(Constants::WINDOW_Y_SIZE), Constants::WINDOW_X_SIZE, Constants::WINDOW_Y_SIZE) };

  Mandelbrot mandel = { Constants::WINDOW_X_SIZE, Constants::WINDOW_Y_SIZE, Constants::N_MAX, Constants::THREAD_COUNT, std::pair<double, double>(-2.0f, 2.0f), std::pair<double, double>(-2.0f, 2.0f) };

  StatsBox sb = { 25.f, -1.f * Constants::WINDOW_Y_SIZE };

  sb.addStat("Update time", "0");

  // TODO: And is in focus
  while (window.isOpen()) {
    if (!window.hasFocus())
      continue;

    // SF events
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }

      if (event.type == sf::Event::TextEntered) {
        sf::String text = event.text.unicode;
        if (text == "r") {
          mandel.resetView();
        }
      }

      // KEYBOARD SCROLL
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::A) {
          mandel.zoom(0.5f);
        }
        else if (event.key.code == sf::Keyboard::Z) {
          mandel.zoom(2.0f);
        }
      }

      // MOUSE SCROLL
      if (event.type == sf::Event::MouseWheelScrolled) {
        // Mouse wheel
        if (event.mouseWheelScroll.delta > 0) {
          //zoom out
          mandel.zoom(0.5f);
        } else {
          //zoom in
          mandel.zoom(2.0f);
        }
      }
    }


    // Update mandel set
    auto timeStart = std::chrono::high_resolution_clock::now();
    mandel.runUpdate(sf::Mouse::getPosition(window));
    auto timeStop = std::chrono::high_resolution_clock::now();
    long int updateTime = std::chrono::duration_cast<std::chrono::milliseconds>(timeStop - timeStart).count();
    if (updateTime > 10) {
      sb.setValue("Update time", std::to_string(updateTime) + "ms");
    }

    // clear draw display
    window.clear();
    window.setView(mandel.getView());
    window.draw(mandel.toSprite());
    window.setView(guiView);
    window.draw(sb);


    window.display();
  }

  return 0;
}