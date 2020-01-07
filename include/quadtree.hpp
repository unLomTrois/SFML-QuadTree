#ifndef QT_TREE_H
#define QT_TREE_H

#include <SFML/Graphics.hpp>

#include <vector>

#include "node.hpp"
#include "point.hpp"

namespace qt {
	class QuadTree {
		friend point;
	public:
		QuadTree();
		QuadTree(node boundary);
		~QuadTree();

		
		//функции
		bool insert(point *p);
		void subdivide();
		std::vector<qt::point*> query(node node);

		void update();
		void collide();

		void show(sf::RenderWindow *window, sf::Color color);

	private:
		static unsigned int capacity;
		static QuadTree *root;

		QuadTree *parent = this;

		//Потомки
		QuadTree *nw = nullptr;
		QuadTree *ne = nullptr;
		QuadTree *sw = nullptr;
		QuadTree *se = nullptr;

		std::vector<point*> points;
		node boundary;
		bool is_divided = false;

		void clear();
	};
}

#endif // QT_TREE_H