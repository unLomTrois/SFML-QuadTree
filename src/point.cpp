#include "point.hpp"

qt::point::point(){
	std::cout << "void point" << std::endl;
}

qt::point::point(float x, float y) : x(x), y(y) {
	std::cout << "add point" << std::endl;
}


