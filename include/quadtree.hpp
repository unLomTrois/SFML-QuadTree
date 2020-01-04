#ifndef QT_TREE_H
#define QT_TREE_H

#include <SFML/Graphics.hpp>

#include <vector>

#include "node.hpp"
#include "point.hpp"

namespace qt {
	class QuadTree {
	public:
		QuadTree();
		QuadTree(node boundary);
		~QuadTree();

		bool is_divided = false; //проверка на деление
		
		//функции
		bool insert(point *p);
		void subdivide();
		std::vector<qt::point*> query(node node);

		void show(sf::RenderWindow *window, sf::Color color, sf::Font &font);

	private:
		static unsigned int capacity;

		node boundary;

		static QuadTree *root; // корень

		QuadTree *parent = nullptr; // родитель

		//Потомки
		QuadTree *nw = nullptr;
		QuadTree *ne = nullptr;
		QuadTree *sw = nullptr;
		QuadTree *se = nullptr;

		std::vector<point*> points;

		// функции
		void init();
	};
}

#endif // QT_TREE_H