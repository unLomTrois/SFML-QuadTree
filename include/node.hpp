#ifndef NODE_HPP
#define NODE_HPP

namespace qt {
	template<typename T>
	struct node {
		float x, y, w, h;

		node(float x = 0, float y = 0, float w = 0, float h = 0);
		node(T &p, float w, float h);
	
		bool containsPoint(T &p);
		bool intersectNode(node node);
	};
}

#include "node.inl"

#endif // NODE_HPP
