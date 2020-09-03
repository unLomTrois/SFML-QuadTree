#include "application.hpp"

#include <chrono>
#include <iostream>

#include "effolkronium/random.hpp"

// get base random alias which is auto seeded and has static API and internal state
using Random = effolkronium::random_static;

application::application(const sf::VideoMode &window_size) {
  window = new sf::RenderWindow(window_size, "SFML-QuadTree");
  window->setFramerateLimit(60);

  size = qt::node<qt::point>(0, 0, window_size.width, window_size.height);

  // QT Init
  qt = new qt::QuadTree<qt::point>(
      qt::node<qt::point>(size.w / 2, size.h / 2, size.w / 2, size.h / 2));

  for (int i = 0; i < 1000; ++i) {
    qt::point::create(Random::get(10, 720), Random::get(10, 720));
  }
}

application::~application() { delete window; }

void application::show() {
  qt::node<qt::point> check(100, 100, 100, 100);

  sf::Time time;
  sf::Clock clock;

  while (window->isOpen()) {
    sf::Event event;
    while (window->pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window->close();
      }

      if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
          qt::point::create(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);
        }
      }

      /*if (event.type == sf::Event::MouseMoved){
        check.x = sf::Mouse::getPosition(*window).x;
        check.y = sf::Mouse::getPosition(*window).y;
      }*/
    }

    window->clear(sf::Color::Black);

    // qt->show(window, sf::Color::Transparent);
    // showNode(window, check, sf::Color::Cyan);

    for (auto &&point : qt::point::points) {
      point->move();
    }

    qt->update();

    qt->collide();

    for (auto &&point : qt::point::points) {
      window->draw(point->c);
    }

    window->display();

    time = clock.getElapsedTime();
    clock.restart().asSeconds();
    std::cout << 1.0f / time.asSeconds() << std::endl;
  }
}

void application::showNode(sf::RenderWindow *window, qt::node<qt::point> node, sf::Color color) {
  sf::RectangleShape rectNode;
  rectNode.setOutlineThickness(-2.f);

  rectNode.setFillColor(sf::Color::Transparent);
  rectNode.setOutlineColor(color);

  rectNode.setPosition(node.x - node.w, node.y - node.h);

  rectNode.setSize(sf::Vector2f(node.w * 2, node.h * 2));

  window->draw(rectNode);
}