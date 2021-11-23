#include <iostream>

#include <SFML/Graphics.hpp>

#include "MandelBrot.cpp"
#include "StatsBox.cpp"


// TODO: multithread mandelbrot calculations, split screen into sections
// TODO: Only recalculate screen when zoom reaches THRESHHOLD. Display old calculations until the new one is fully ready.

const int WINDOW_X_SIZE = 1920;
const int WINDOW_Y_SIZE = 1080;
const int N_MAX = 25;
const float MOVE_SPEED = 1.0f;
const float EDGE_PANE = 0.15f;

int main(int, char *[])
{

  sf::RenderWindow window(sf::VideoMode(WINDOW_X_SIZE, WINDOW_Y_SIZE), "Mandelbrot");
  sf::Font tempFont = {};
  tempFont.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf");
  sf::Text temp = { "testing", tempFont };
  sf::View guiView{ sf::FloatRect(0.0f, -1.0f * static_cast<float>(WINDOW_Y_SIZE), WINDOW_X_SIZE, WINDOW_Y_SIZE) };

  Mandelbrot mandel = { WINDOW_X_SIZE, WINDOW_Y_SIZE, N_MAX, std::pair<double, double>(-2.0f, 2.0f), std::pair<double, double>(-2.0f, 2.0f) };
  mandel.runUpdate(sf::Mouse::getPosition(window));

  StatsBox sb = { 0, -1 * static_cast<int>(WINDOW_Y_SIZE) };
  std::shared_ptr<StatsEntry> updateTimeStat = sb.addStat({ "update_time" }, { "0" });

  // TODO: And is in focus
  while (window.isOpen()) {

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

      if (event.type == sf::Event::MouseWheelScrolled) {
        // Mouse wheel
        if (event.mouseWheelScroll.delta > 0) {
          //zoom out
          mandel.zoom(0.5f);
        } else {
          //zoom in
          mandel.zoom(2.0f);
        }
        // Panning
      }
    }


    // Update mandel set
    auto timeStart = std::chrono::high_resolution_clock::now();
    mandel.runUpdate(sf::Mouse::getPosition(window));
    auto timeStop = std::chrono::high_resolution_clock::now();
    long int updateTime = std::chrono::duration_cast<std::chrono::milliseconds>(timeStop - timeStart).count();
    updateTimeStat->setValue(std::to_string(updateTime) + "ms");

    // Update stats box
    sb.update();

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