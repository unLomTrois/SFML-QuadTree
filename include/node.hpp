#ifndef NODE_HPP
#define NODE_HPP

#include "point.hpp"

namespace qt {

struct node {
  float x, y, w, h;

  node(float x = 0, float y = 0, float w = 0, float h = 0);
  node(const qt::point &p, float w, float h);

  bool containsPoint(const qt::point &p) const;
  bool intersectNode(const node &node) const;
};
}  // namespace qt

#endif  // NODE_HPP
