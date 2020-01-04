#include "point.hpp"

int qt::point::count = 0;
std::vector<qt::point> qt::point::vect;

qt::point::point(){
	std::cout << "void point" << std::endl;
}

qt::point::point(float x, float y) : x(x), y(y) {
	count++;

	std::cout << "add point: " << count << std::endl;
}

qt::point::~point(){
	// count--;
	std::cout << "deleted" << std::endl;
}

void qt::point::init(int cap){
	vect.reserve(cap);
}

void qt::point::create(float x, float y) {
	vect.reserve(200);

	vect.emplace_back(x, y);
}