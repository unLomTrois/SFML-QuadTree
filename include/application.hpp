#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Window.hpp>

#include "node.hpp"
#include "point.hpp"
#include "quadtree.hpp"

class application {
 public:
  application(const sf::VideoMode &window_size);
  ~application();

  void show();
  void showNode(sf::RenderWindow *window, qt::node node, sf::Color color);

 private:
  qt::node size;
  sf::RenderWindow *window;
  qt::QuadTree<qt::point> *qt;
};

#endif  // APPLICATION_HPP
