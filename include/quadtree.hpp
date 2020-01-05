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

		bool is_divided = false; //проверка на деление
		
		//функции
		bool insert(point *p);
		void subdivide();
		std::vector<qt::point*> query(node node);

		void show(sf::RenderWindow *window, sf::Color color);

		void update(point *p);

		static void init(QuadTree &bindRoot);
		void updateChildren();

	private:
		static unsigned int capacity;
		static QuadTree *root; // корень

		node boundary;

		QuadTree *parent = this; // родитель

		//Потомки
		QuadTree *nw = nullptr;
		QuadTree *ne = nullptr;
		QuadTree *sw = nullptr;
		QuadTree *se = nullptr;

		std::vector<point*> points;

		
	};
}

#endif // QT_TREE_H