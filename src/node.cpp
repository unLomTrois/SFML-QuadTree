#include "node.hpp"

namespace qt {

node::node(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}

node::node(const qt::point &p, float w, float h) : x(p.x), y(p.y), w(w), h(h) {}

bool node::containsPoint(const qt::point &p) const {
  if ((p.x >= x - w) && (p.y >= y - h) && (p.x <= x + w) && (p.y <= y + h)) {
    return true;
  } else {
    return false;
  }
}

bool node::intersectNode(const node &node) const {
  return !(node.x - node.w > x + w || node.x + node.w < x - w || node.y - node.h > y + h ||
           node.y + node.h < y - h);
}

}  // namespace qt