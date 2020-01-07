#ifndef QT_TREE_H
#define QT_TREE_H

#include <SFML/Graphics.hpp>

#include <vector>

#include "node.hpp"
#include "point.hpp"

namespace qt {

	template<typename T>
	class QuadTree {
		friend point;
	public:
		QuadTree();
		QuadTree(node boundary);
		~QuadTree();

		
		//функции
		bool insert(T *p);
		void subdivide();
		std::vector<T*> query(node node);

		void update();
		void collide();

		void show(sf::RenderWindow *window, sf::Color color);

	private:
		static unsigned int capacity;
		static QuadTree *root;

		QuadTree *parent = this;

		//Потомки
		QuadTree<T> *nw = nullptr;
		QuadTree<T> *ne = nullptr;
		QuadTree<T> *sw = nullptr;
		QuadTree<T> *se = nullptr;

		std::vector<T*> points;
		node boundary;
		bool is_divided = false;

		void clear();
	};
}

#endif // QT_TREE_H