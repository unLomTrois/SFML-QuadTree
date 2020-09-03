#ifndef NODE_HPP
#define NODE_HPP

namespace qt {
template <typename T>
struct node {
  float x, y, w, h;

  node(float x = 0, float y = 0, float w = 0, float h = 0);
  node(const T &p, float w, float h);

  bool containsPoint(const T &p) const;
  bool intersectNode(const node &node) const;
};
}  // namespace qt

#include "node.inl"

#endif  // NODE_HPP
