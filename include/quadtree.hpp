#ifndef QT_TREE_H
#define QT_TREE_H

#include <vector>

#include "node.hpp"
#include "point.hpp"

namespace qt {
	class QuadTree {
	public:
		QuadTree();
		QuadTree(node boundary);
		~QuadTree();

		node boundary;
		void subdivide();
		bool is_divided = false; //проверка на деление

		// std::vector<char> v = {'a'};
		//Потомки
		
		QuadTree *nw;
		QuadTree *ne;
		QuadTree *sw;
		QuadTree *se;
		
		//функции
		bool insert(point *p);
	private:
		static unsigned int capacity;
		void init();

		// point points;
		std::vector<point*> points;
	};
}

#endif // QT_TREE_H