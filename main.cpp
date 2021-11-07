#include <iostream>

#include <SFML/Graphics.hpp>

#include "MandelBrot.cpp"
#include "StatsBox.cpp"


// TODO: Divide classes into separate headers
// TODO: multithread mandelbrot calculations, split screen into sections
// TODO: Only recalculate screen when zoom reaches THRESHHOLD. Display old calculations until the new one is fully ready.


const unsigned int WINDOW_X_SIZE = 1920;
const unsigned int WINDOW_Y_SIZE = 1080;
const unsigned int N_MAX = 255;

int main(int argc, char *argv[])
{


  sf::RenderWindow window(sf::VideoMode(WINDOW_X_SIZE, WINDOW_Y_SIZE), "Mandelbrot");
  sf::Font tempFont = {};
  tempFont.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf");
  sf::Text temp = { "testing", tempFont };

  Mandelbrot mandel = { WINDOW_X_SIZE, WINDOW_Y_SIZE, N_MAX };

  StatsBox sb = { WINDOW_X_SIZE - 300, 300 };
  StatsEntry &updateTimeStat = sb.addStat({ "update_time" }, { "0" });

  while (window.isOpen()) {

    // SF events
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }

      if (event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.delta > 0) {
          //zoom out
          continue;
        } else {
          //zoom in
          continue;
        }
      }
    }

    // clear draw display
    auto timeStart = std::chrono::high_resolution_clock::now();
    mandel.runUpdate();
    auto timeStop = std::chrono::high_resolution_clock::now();
    int updateTime = std::chrono::duration_cast<std::chrono::milliseconds>(timeStop - timeStart).count();
    std::cout << "updatetime: " << updateTime << "ms\n";
    updateTimeStat.setValue(std::to_string(updateTime) + "ms");
    window.clear();
    window.draw(mandel.toSprite());
    //window.draw(temp);
    window.draw(sb);
    window.display();
  }

  return 0;
}