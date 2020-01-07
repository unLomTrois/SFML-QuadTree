#include "quadtree.hpp"

#include <iostream>
#include <string>

unsigned int qt::QuadTree::capacity = 4;

qt::QuadTree* qt::QuadTree::root = nullptr; //корень

qt::QuadTree::QuadTree() {}

qt::QuadTree::QuadTree(node boundary) : boundary(boundary) {
	points.reserve(capacity);
}

qt::QuadTree::~QuadTree(){
	if (is_divided){
		delete nw;
		delete ne;
		delete sw;
		delete se;
	}
	points.clear();
}

void qt::QuadTree::init(QuadTree *bindRoot){
	root = bindRoot;
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

	nw->parent = this;
	ne->parent = this;
	sw->parent = this;
	se->parent = this;

	for(auto&& point : points) {
		nw->insert(point);
		ne->insert(point);
		sw->insert(point);
		se->insert(point);
	}

	points.clear();
}


bool qt::QuadTree::insert(point *p){
	bool ret = false;

	if (!boundary.containsPoint(*p)){

	} else {
		if (!is_divided){
			if (points.size() < capacity){
				points.push_back(p);
				p->bindqt = this;

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

void qt::QuadTree::update(){
	if (is_divided){
		clear();
	
		for(auto&& point : qt::point::points) {
			insert(point);
			// point->collide();
		}
	}

	// updateChildren();
}

void qt::QuadTree::clear(){
	delete nw;
	delete ne;
	delete sw;
	delete se;

	is_divided = false;
	points.clear();
}

void qt::QuadTree::collide(){
	if (is_divided){
		nw->collide();
		ne->collide();
		sw->collide();
		se->collide();
	} else {
		for(auto&& point : points) {
			point->collide();
		}
	}
}
/*
void qt::QuadTree::updateChildren(){
	if (is_divided) {
		std::vector<qt::point*> que = query(boundary);

		if (que.size() < 4){
			
			delete nw;
			delete ne;
			delete sw;
			delete se;

			is_divided = false;

			for(auto&& point : que) {
				parent->insert(point);
			}
		} else {
			nw->updateChildren();
			ne->updateChildren();
			sw->updateChildren();
			se->updateChildren();
		}
	}
}
*/

void qt::QuadTree::show(sf::RenderWindow *window, sf::Color color){
	if (is_divided){
		nw->show(window, sf::Color::Red);
		ne->show(window, sf::Color::Blue);
		sw->show(window, sf::Color::Yellow);
		se->show(window, sf::Color::White);
	} else {
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

		window->draw(node);
	}
}

std::vector<qt::point*> qt::QuadTree::query(node node){
	std::vector<qt::point*> ret;

	if (!boundary.intersectNode(node)){

	} else {
		if (!is_divided){
			for(auto&& point : points) {
				if (node.containsPoint(*point)){
					ret.push_back(point);
				}
			}
		} else {
			std::vector<qt::point*> nwRet = nw->query(node);
			std::vector<qt::point*> neRet = ne->query(node);
			std::vector<qt::point*> swRet = sw->query(node);
			std::vector<qt::point*> seRet = se->query(node);

			ret.insert(ret.end(), nwRet.begin(), nwRet.end());
			ret.insert(ret.end(), neRet.begin(), neRet.end());
			ret.insert(ret.end(), swRet.begin(), swRet.end());
			ret.insert(ret.end(), seRet.begin(), seRet.end());
		}
	}

	return ret;
}
