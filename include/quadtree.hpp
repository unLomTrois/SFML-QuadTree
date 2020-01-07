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

		bool is_divided = false;
		
		//функции
		bool insert(point *p);
		void subdivide();
		std::vector<qt::point*> query(node node);

		void show(sf::RenderWindow *window, sf::Color color);

		void update();

		static QuadTree *root;

		void collide();

	private:
		static unsigned int capacity;

		node boundary;

		QuadTree *parent = this;

		//Потомки
		QuadTree *nw = nullptr;
		QuadTree *ne = nullptr;
		QuadTree *sw = nullptr;
		QuadTree *se = nullptr;

		std::vector<point*> points;

		void clear();
		void updateChildren();
	};
}

#endif // QT_TREE_H