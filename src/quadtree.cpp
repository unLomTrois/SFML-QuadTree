#include "quadtree.hpp"

#include <iostream>
#include <string>

template<typename T>
unsigned int qt::QuadTree<T>::capacity = 4;

template<typename T>
qt::QuadTree<T>* qt::QuadTree<T>::root = nullptr; //корень

template<typename T>
qt::QuadTree<T>::QuadTree() {}

template<typename T>
qt::QuadTree<T>::QuadTree(qt::node boundary) : boundary(boundary) {
	points.reserve(capacity);

	if (root == nullptr) {
		root = this;
	}
}

template<typename T>
qt::QuadTree<T>::~QuadTree(){
	if (is_divided){
		delete nw;
		delete ne;
		delete sw;
		delete se;
	}
	points.clear();
}

template<typename T>
void qt::QuadTree<T>::subdivide(){
	is_divided = true;

	float x = boundary.x;
	float y = boundary.y;
	float w = boundary.w;
	float h = boundary.h;

	nw = new QuadTree<T>(node(x - w/2, y - h/2, w/2, h/2));
	ne = new QuadTree<T>(node(x + w/2, y - h/2, w/2, h/2));
	sw = new QuadTree<T>(node(x - w/2, y + h/2, w/2, h/2));
	se = new QuadTree<T>(node(x + w/2, y + h/2, w/2, h/2));

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

template<typename T>
bool qt::QuadTree<T>::insert(T *p){
	bool ret = false;

	if (!boundary.containsPoint(*p)){

	} else {
		if (!is_divided){
			if (points.size() < capacity){
				for(auto&& exP : points) {
					if (p->x == exP->x && p->y == exP->y){
						return false; //same pos
					}
				}

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

template<typename T>
void qt::QuadTree<T>::update(){
	if (is_divided){
		clear();
	
		for(auto&& point : qt::point::points) {			
			while (!insert(point)){
				point->move();
			}
		}
	}
}

template<typename T>
void qt::QuadTree<T>::clear(){
	delete nw;
	delete ne;
	delete sw;
	delete se;

	is_divided = false;
	points.clear();
}

template<typename T>
void qt::QuadTree<T>::collide(){
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

template<typename T>
void qt::QuadTree<T>::show(sf::RenderWindow *window, sf::Color color){
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

template<typename T>
std::vector<T*> qt::QuadTree<T>::query(node node){
	std::vector<T*> ret;

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

template class qt::QuadTree<qt::point>;