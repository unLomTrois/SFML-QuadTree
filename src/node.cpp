#include "node.hpp"

qt::node::node(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}

qt::node::node(point &p, float w, float h) : x(p.x), y(p.y), w(w), h(h) {}

bool qt::node::containsPoint(point &p){
	if ((p.x >= x - w) && (p.y >= y - h) &&
		(p.x <= x + w) && (p.y <= y + h)) {
		return true;
	} else {
		return false;
	}
}

bool qt::node::intersectNode(node node){
	return !(
		node.x - node.w > x + w || 
		node.x + node.w < x - w ||
		node.y - node.h > y + h ||
		node.y + node.h < y - h
	);
}