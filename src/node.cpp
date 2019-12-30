#include "node.hpp"

qt::node::node(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {}

qt::node::node(point &p, int w, int h) : x(p.x), y(p.y), w(w), h(h) {}

bool qt::node::containsPoint(point &p){
	if ((p.x >= x - w) && (p.y >= y - h) &&
		(p.x <= x + w) && (p.y <= y + h)) {
		return true;
	} else {
		return false;
	}
}