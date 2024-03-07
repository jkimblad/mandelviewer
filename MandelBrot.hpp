#pragma once

#include <SFML/Graphics.hpp>

#include "SFHelper.hpp"

class Mandelbrot
{
public:
  // Constructor
  /*!
   * \brief Constructor.
   *
   * \param window_x_size_ Window width given in pixels.
   * \param window_y_size_ Window height given in pixels.
   * \param n_max_ Amount of iterations when calculating each pixel value.
   * \param threadNo Amount of threads to divide the workload between.
   * \param xRange_ Initial range of x values for the set.
   * \param yRange_ Initial range of y values for the set.
   */
  Mandelbrot(const unsigned int, const unsigned int, const unsigned int, const unsigned int, std::pair<double, double>, std::pair<double, double>);

  // Functions
  /*!
   * \brief Updates the current mandel representation.
   *
   * Checks if the view has been updated and should be renedered onto the screen. Also handles tha paning around the image using the mouse.
   *
   * \param mousePos The users current mouse position, used to update paning.
   */
  void runUpdate(const sf::Vector2i &);
  /*!
   * \brief Updates the on-screen rendered image according to current location and zoom.
   *
   * This function kickstarts n amount of threads, each responsible for calculating the pixel values of a sub-region of the total picture. Once all threads are finished, the full picture has been rendered.
   */
  void updateImage();
  /*!
   * \brief Getter for view.
   *
   * \return The current view.
   */
  sf::View &getView();
  /*!
   * \brief Casts the current mandel image as a sf::Sprite.
   *
   * Transforms the current view of the mandelbrot stored as a sf::Image to sf::Texture and then to a sf::Sprite which is returned to the user.
   *
   * \return The current mandel image.
   */
  sf::Sprite &toSprite();
  /*!
   * \brief Zooms the rendered image in or out.
   *
   * Zooms the rendered image by scaling it up either larger or smaller.
   *
   * \param zoomFactor The factor to which the image should be zoomed to. Values between 0-1 indicate a negative zoom (zooming out), and values greated than 1 indicate a positive zoom (zoom in).
   * */
  void zoom(float);
  /*!
   * \brief Renders a new image for the current location.
   *
   * Calling this function will re-render the mandelbrot set for the current position at the apropriate zoom-level.
   * */
  void resetView();


private:
  // Functions
  /*!
   * \brief Checks if the users mouse is hovering inside the window.
   *
   * Returns true if the users mouse is within the applications window borders in the operating system. If the mouse is outside, the function will return false.
   *
   * \param mousePos Takes a sf::Vector2i that denotes the mouse position.
   *
   * \return If the mouse is inside or outside the application window.
   * */
  bool isMouseInWindow(const sf::Vector2i);
  void updatePanning(const sf::Vector2i &mousePos);
  sf::Color colorToHSV(int, float, float);
  void mandelWorker(const sf::Vector2u, const sf::Vector2u);

  // Objects
  unsigned int windowXSize {};
  unsigned int windowYSize {};
  unsigned int n_max {};
  unsigned int noThreads {4};
  std::pair<double, double> xRange { -2.0f, 2.0f };
  std::pair<double, double> yRange { -2.0f, 2.0f };
  sf::View view {};
  sf::Image drawImage {};
  sf::Texture drawTexture {};
  sf::Sprite drawSprite {};
  bool updateTime {true};
  float MOVE_SPEED_FACTOR {0.001f};
  float EDGE_PANE {0.15f};
  sf::Vector2f refreshSize {};
  sf::Vector2f refreshPosition {};
};
