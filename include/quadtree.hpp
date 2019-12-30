#ifndef QT_TREE_H
#define QT_TREE_H

// #include <cstddef>
// #include <iostream>

#include <string>

#include "point.hpp"
#include "node.hpp"

namespace qt {
	class QuadTree {
	private:	
		int pointsAmount = 0;
		static const int pointsCapacity = 4;
		void init();

		point *points;

		std::string corner = "base";
		void setCorner(std::string corn);
	public:
		QuadTree();
		QuadTree(node boundary);
		~QuadTree();

		node boundary;
		void subdivide();
		bool is_divided = false; //проверка на деление

		//Потомки
		
		QuadTree *nw;
		QuadTree *ne;
		QuadTree *sw;
		QuadTree *se;
		
		bool insert(point &p);

	};
}

#endif // QT_TREE_H