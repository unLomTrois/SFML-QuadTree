#include "point.hpp"

std::vector<qt::point> qt::point::points;

qt::point::point() {}

qt::point::point(float x, float y) : x(x), y(y) {}

qt::point::~point() {}

void qt::point::init(int cap){
	points.reserve(cap);
}

void qt::point::create(float x, float y) {
	points.reserve(200);

	points.emplace_back(x, y);
}