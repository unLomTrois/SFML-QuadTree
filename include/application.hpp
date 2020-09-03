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
  application(unsigned int w = 800, unsigned int h = 800);
  ~application();

  void base();
  void show();
  void showNode(sf::RenderWindow *window, qt::node<qt::point> node, sf::Color color);

 private:
  qt::node<qt::point> size;
  sf::RenderWindow *window;
  qt::QuadTree<qt::point> *qt;
};

#endif  // APPLICATION_HPP
