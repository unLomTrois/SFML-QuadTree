#include "quadtree.hpp"

#include <iostream>

qt::QuadTree::QuadTree(){
	boundary = node(0, 0, 0, 0);

	init();
}

qt::QuadTree::QuadTree(node boundary) : boundary(boundary) {
	init();
}

qt::QuadTree::~QuadTree(){
	// delete points;

	if (is_divided){
		delete nw;
		delete ne;
		delete sw;
		delete se;
	}
}

void qt::QuadTree::init(){
	points = new point [4];

	nw = nullptr;
	ne = nullptr;
	sw = nullptr;
	se = nullptr;
}

void qt::QuadTree::subdivide(){
	is_divided = true;

	int x = boundary.x;
	int y = boundary.y;
	int w = boundary.w;
	int h = boundary.h;

	nw = new QuadTree(node(x - w/2, y - h/2, w/2, h/2));
	ne = new QuadTree(node(x + w/2, y - h/2, w/2, h/2));
	sw = new QuadTree(node(x - w/2, y + h/2, w/2, h/2));
	se = new QuadTree(node(x + w/2, y + h/2, w/2, h/2));

	nw->setCorner("nw");
	ne->setCorner("ne");
	sw->setCorner("sw");
	se->setCorner("se");

	for (int i = 0; i < 4; ++i){
		nw->insert(points[i]);
		ne->insert(points[i]);
		sw->insert(points[i]);
		se->insert(points[i]);
	}

	delete points;
	// pointsAmount = NULL;
}

void qt::QuadTree::setCorner(std::string corn){
	corner = corn;
}


bool qt::QuadTree::insert(point &p){
	bool ret = false;

	// std::cout << corner << ": ";
	if (!boundary.containsPoint(p)){
		ret = false;
	} else {
		if (pointsAmount < pointsCapacity){
			points[pointsAmount] = p;
			pointsAmount++;
			// std::cout << "pa: " << pointsAmount << std::endl;
			
			ret = true;
		}

		if (!is_divided){
			if (pointsAmount == pointsCapacity){
			subdivide();
			}
		} else {
			ret = (
				nw->insert(p) || ne->insert(p) ||
				sw->insert(p) || se->insert(p)
			);
		}
	}

	return ret;
}



