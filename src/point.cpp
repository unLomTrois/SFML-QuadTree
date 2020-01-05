#include "point.hpp"

#include "random.hpp"

#include <SFML/Graphics.hpp>

#include <cmath>

std::vector<qt::point> qt::point::points;
qt::QuadTree* qt::point::rootQT;


qt::point::point() {}

qt::point::point(float x, float y) : x(x), y(y) {
	c = sf::CircleShape(radius, 50);
	c.setFillColor(color);
	c.setPosition(x - radius, y - radius);
}

qt::point::~point() {}

void qt::point::init(int cap, QuadTree &qt){
	points.reserve(cap);
	rootQT = &qt;
}

void qt::point::create(float x, float y) {
	points.reserve(200);

	points.emplace_back(x, y);
}

void qt::point::move(){
	x += random(-1, 1);
	y += random(-1, 1);

	if (!(
		x > 0 && x < 720 &&
		y > 0 && y < 720
		)){
		
		x = random(10, 710);
		y = random(10, 710);
	}

	c.setPosition(x - radius, y - radius);

	bindQT->update(this);

	collide();
}

void qt::point::collide(){
	std::vector<qt::point*> coll = bindQT->root->query(qt::node(x, y, radius*2, radius*2));

	if (coll[0] == this && coll.size() == 1) {		
		color = sf::Color::Red;
		c.setFillColor(color);
	} else {
		unsigned int num = 1;
		for(auto&& p : coll) {
			if (p != this){
				if (sqrt((p->x - x) * (p->x - x) + (p->y - y) * (p->y - y)) <= radius*2){
					color = sf::Color::Green;
					c.setFillColor(color);
					p->color = color;
					p->c.setFillColor(p->color);
				} else {
					num++;
				}
			}
		}

		if (num == coll.size()) {
			color = sf::Color::Red;
			c.setFillColor(color);
		}
	}
}