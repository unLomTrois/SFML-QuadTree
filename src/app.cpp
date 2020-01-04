#include "app.hpp"

#include <iostream>

#include "random.hpp"

app::app(unsigned int w, unsigned int h){
	window = new sf::RenderWindow(sf::VideoMode(w, h), "SFML-QuadTree");

	size = qt::node(0, 0, w, h);

	base();
}

app::~app(){
	delete window;
}

void app::base(){
	qt = qt::QuadTree(qt::node(size.w / 2, size.h / 2, size.w / 2, size.h / 2));

	qt::point::init(1000);

	for (int i = 0; i < 0; ++i){
		qt::point::create(random(10, 720), random(10, 720));
	}
	
	for(auto&& point : qt::point::vect) {
		qt.insert(&point);
	}

}

void app::show(){
	while (window->isOpen()){
		sf::Event event;
		while (window->pollEvent(event)){
			if (event.type == sf::Event::Closed){
				window->close();
			}

			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					
					qt::point::create(
						sf::Mouse::getPosition(*window).x, 
						sf::Mouse::getPosition(*window).y
					);

					qt.insert(&qt::point::vect.back());
				}

				if (event.mouseButton.button == sf::Mouse::Right) {
					std::cout << qt::point::vect.capacity() << std::endl;
				}
			}
		
		}

		window->clear(sf::Color::Black);

		showNodes(window, &qt, sf::Color::Transparent);
	
		for(auto&& point : qt::point::vect) {
			sf::CircleShape c(2, 4);
			c.setFillColor(sf::Color::Red);
			c.setPosition(point.x, point.y);

			window->draw(c);
		}
	
		window->display();
	}
}

void app::showNodes(sf::RenderWindow *window, qt::QuadTree *qt, sf::Color color){
	sf::RectangleShape node;
	node.setOutlineThickness(-1.f);
	
	node.setFillColor(sf::Color::Transparent);
	node.setOutlineColor(color);
	node.setSize(
		sf::Vector2f(
			qt->boundary.w * 2, 
			qt->boundary.h * 2
		)
	);

	node.setPosition(
		qt->boundary.x - qt->boundary.w, 
		qt->boundary.y - qt->boundary.h
	);
	
	
	if (qt->is_divided){
		showNodes(window, qt->nw, sf::Color::Red);
		showNodes(window, qt->ne, sf::Color::Blue);
		showNodes(window, qt->sw, sf::Color::Yellow);
		showNodes(window, qt->se, sf::Color::White);
	}

	window->draw(node);
};
