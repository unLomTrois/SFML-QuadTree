#ifndef QT_TREE_H
#define QT_TREE_H

#include <SFML/Graphics.hpp>

#include <vector>

#include "node.hpp"

namespace qt {

template <typename T>
class QuadTree {
  friend T;

 public:
  QuadTree();
  QuadTree(node<T> boundary);
  ~QuadTree();

  //функции
  bool insert(T *p);
  void subdivide();
  std::vector<T *> query(const node<T> &node);

  void update();
  void collide();

  void show(sf::RenderWindow *window, sf::Color color);

 private:
  static unsigned int capacity;
  static QuadTree *root;

  QuadTree *parent = this;

  //Потомки
  QuadTree<T> *nw = nullptr;
  QuadTree<T> *ne = nullptr;
  QuadTree<T> *sw = nullptr;
  QuadTree<T> *se = nullptr;

  std::vector<T *> points;
  node<T> boundary;
  bool is_divided = false;

  void clear();
};
}  // namespace qt

#include "quadtree.inl"

#endif  // QT_TREE_H