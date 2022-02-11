#include "point.hpp"

#include <chrono>
#include <cmath>

#include "quadtree.hpp"

#include "effolkronium/random.hpp"

// get base random alias which is auto seeded and has static API and internal state
using Random = effolkronium::random_static;

std::vector<qt::point *> qt::point::points;

qt::point::point() {}

qt::point::point(float x, float y) : x(x), y(y) {
  c = sf::CircleShape(radius, 25);
  c.setFillColor(color);
  c.setPosition(x - radius, y - radius);

  is_collided = false;
}

qt::point::~point() {}

void qt::point::create(float x, float y) {
  points.emplace_back() = new qt::point(x, y);

  while (!qt::QuadTree<qt::point>::root->insert(points.back())) {
    points.back()->move();
  }
}

void qt::point::move() {
  auto kek = sf::Vector2f(cos(direction), sin(direction));

  x += kek.x;//Random::get(-velocity, velocity);
  y += kek.y;//Random::get(-velocity, velocity);

  direction += 0.01f + sin(y) + cos(x);


  if (!(x > 0 && x < 720 && y > 0 && y < 720)) {
    x = Random::get(10, 710);
    y = Random::get(10, 710);
  }

  c.setPosition(x - radius, y - radius);
}

bool qt::point::collide() {
  std::vector<qt::point *> coll =
      qt::QuadTree<qt::point>::root->query(qt::node<qt::point>(x, y, radius * 2.5, radius * 2.5));

  if (coll[0] == this && coll.size() == 1) {
    is_collided = false;

  } else {
    unsigned int num = 1;
    for (auto &&p : coll) {
      if (p != this) {
        if (sqrt((p->x - x) * (p->x - x) + (p->y - y) * (p->y - y)) <= radius * 2) {
          is_collided = true;
        } else {
          num++;
        }
      }
    }

    if (num == coll.size()) {
      is_collided = false;
    }
  }

  color = (is_collided ? sf::Color::Green : sf::Color::Red);
  c.setFillColor(color);

  return is_collided;
}