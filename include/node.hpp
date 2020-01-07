#ifndef NODE_HPP
#define NODE_HPP

#include "point.hpp"

namespace qt {
	struct node {
		float x, y, w, h;

		node(float x = 0, float y = 0, float w = 0, float h = 0);
		node(point &p, float w, float h);
	
		bool containsPoint(point &p);
		bool intersectNode(node node);
	};
}


#endif // NODE_HPP
