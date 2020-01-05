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

		sf::Color color = sf::Color::Red;
		int radius = 2;
		sf::CircleShape c;

		point();
		point(float x, float y);
		~point();

		static std::vector<point> points;
		static void create(float x, float y);
		static void init(int cap, QuadTree &qt);
		static QuadTree *rootQT;

		QuadTree *bindQT;

		void move();
		void collide();
	};
}

#endif // QT_POINT_HPP
