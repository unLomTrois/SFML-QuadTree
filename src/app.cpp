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

		qt.show(window, sf::Color::Transparent);
		
		for(auto&& point : qt::point::vect) {
			sf::CircleShape c(point.radius, 4);
			c.setFillColor(point.color);
			c.setPosition(point.x, point.y);

			window->draw(c);
		}
	
		window->display();
	}
}