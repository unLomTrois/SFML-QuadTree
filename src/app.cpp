#include "app.hpp"

#include <iostream>

#include "random.hpp"

app::app(unsigned int w, unsigned int h){
	window = new sf::RenderWindow(sf::VideoMode(w, h), "SFML-QuadTree");
	window->setFramerateLimit(60);

	size = qt::node(0, 0, w, h);

	base();
}

app::~app(){
	delete window;
}

void app::base(){
	qt = qt::QuadTree(qt::node(size.w / 2, size.h / 2, size.w / 2, size.h / 2));
	qt::QuadTree::init(qt);

	qt::point::init(2000, qt);

	for (int i = 0; i < 1000; ++i){
		qt::point::create(random(10, 720), random(10, 720));
	}

	for(auto&& point : qt::point::points) {
		qt.insert(&point);
	}

}

void app::show(){
	// qt::node check(random(10, 720), random(10, 720), random(200), random(200));

	sf::Time time;
	sf::Clock clock;

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

					qt.insert(&qt::point::points.back());
				}

				if (event.mouseButton.button == sf::Mouse::Right) {
					
				}
			}
		}

		window->clear(sf::Color::Black);

		time = clock.getElapsedTime();
	    clock.restart().asSeconds();
		std::cout << 1.0f/time.asSeconds() << std::endl;

		// qt.show(window, sf::Color::Transparent);
		// showNode(window, check, sf::Color::Cyan);

		for(auto&& point : qt::point::points) {
			point.move();

			window->draw(point.c);
		}
	
		window->display();
	}
}

void app::showNode(sf::RenderWindow *window, qt::node node, sf::Color color){
	sf::RectangleShape rectNode;
	rectNode.setOutlineThickness(-2.f);
	
	rectNode.setFillColor(sf::Color::Transparent);
	rectNode.setOutlineColor(color);
	
	rectNode.setPosition(
		node.x - node.w,
		node.y - node.h
	);

	rectNode.setSize(
		sf::Vector2f(
			node.w * 2, 
			node.h * 2
		)
	);
	
	window->draw(rectNode);
}