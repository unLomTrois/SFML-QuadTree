#ifndef QT_POINT_HPP
#define QT_POINT_HPP

#include <iostream>
#include <vector>

namespace qt {
	struct point {
		float x, y;

		point();
		point(float x, float y);
		~point();


		static int count;
		static std::vector<point> vect;
		static void create(float x, float y);
		static void init(int cap);
	};
}

#endif // QT_POINT_HPP
