#include "quadtree.hpp"

#include <iostream>

unsigned int qt::QuadTree::capacity = 4;

qt::QuadTree::QuadTree() {
	init();
}

qt::QuadTree::QuadTree(node boundary) : boundary(boundary) {
	init();
}

qt::QuadTree::~QuadTree(){
	if (is_divided){
		delete nw;
		delete ne;
		delete sw;
		delete se;
	}
}

void qt::QuadTree::init(){
	points.reserve(capacity);

	nw = nullptr;
	ne = nullptr;
	sw = nullptr;
	se = nullptr;
}

void qt::QuadTree::subdivide(){
	is_divided = true;

	float x = boundary.x;
	float y = boundary.y;
	float w = boundary.w;
	float h = boundary.h;

	nw = new QuadTree(node(x - w/2, y - h/2, w/2, h/2));
	ne = new QuadTree(node(x + w/2, y - h/2, w/2, h/2));
	sw = new QuadTree(node(x - w/2, y + h/2, w/2, h/2));
	se = new QuadTree(node(x + w/2, y + h/2, w/2, h/2));

	for(auto&& point : points) {
		nw->insert(point);
		ne->insert(point);
		sw->insert(point);
		se->insert(point);
	}

	points.clear();
	// pointsAmount = NULL;
}


bool qt::QuadTree::insert(point *p){
	bool ret;

	if (!boundary.containsPoint(*p)){
		ret = false;
	} else {
		if (!is_divided){
			if (points.size() < capacity){
				points.push_back(p);
				
				ret = true;
			}

			if (points.size() == capacity){
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

void qt::QuadTree::show(sf::RenderWindow *window, sf::Color color){
	sf::RectangleShape node;
	node.setOutlineThickness(-1.f);
	
	node.setFillColor(sf::Color::Transparent);
	node.setOutlineColor(color);
	node.setSize(
		sf::Vector2f(
			boundary.w * 2, 
			boundary.h * 2
		)
	);

	node.setPosition(
		boundary.x - boundary.w, 
		boundary.y - boundary.h
	);
	
	
	if (is_divided){
		nw->show(window, sf::Color::Red);
		ne->show(window, sf::Color::Blue);
		sw->show(window, sf::Color::Yellow);
		se->show(window, sf::Color::White);
	}

	window->draw(node);
}