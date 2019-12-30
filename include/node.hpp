#ifndef NODE_HPP
#define NODE_HPP

#include "point.hpp"

namespace qt {
	struct node {
		int x, y, w, h;

		node(int x = 0, int y = 0, int w = 0, int h = 0);
		node(point &p, int w, int h);
	
		bool containsPoint(point &p);
	};
}

#endif // NODE_HPP
