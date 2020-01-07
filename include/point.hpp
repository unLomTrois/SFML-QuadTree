#ifndef QT_POINT_HPP
#define QT_POINT_HPP

#include <iostream>
#include <vector>

#include <SFML/Graphics/Color.hpp>

namespace qt {
	class QuadTree;
}

#include "quadtree.hpp"

namespace qt {
	struct point {
		float x, y;

		int radius = 5;
		float velocity = 1;
		bool is_collided;

		sf::Color color = sf::Color::Red;
		sf::CircleShape c;

		point();
		point(float x, float y);
		~point();

		static std::vector<point*> points;
		static void create(float x, float y);

		QuadTree *bindqt;

		void move();
		bool collide();
	};
}

#endif // QT_POINT_HPP
