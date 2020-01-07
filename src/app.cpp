#include "app.hpp"

#include <iostream>

#include "random.hpp"

#include <chrono>


app::app(unsigned int w, unsigned int h){
	window = new sf::RenderWindow(sf::VideoMode(w, h), "SFML-QuadTree");
	window->setFramerateLimit(60);

	size = qt::node<qt::point>(0, 0, w, h);

	base();
}

app::~app(){
	delete window;
}

void app::base(){
	qt = new qt::QuadTree<qt::point>(qt::node<qt::point>(size.w / 2, size.h / 2, size.w / 2, size.h / 2));

	for (int i = 0; i < 1000; ++i){
		qt::point::create(random(10, 720), random(10, 720));
	}
}

void app::show(){
	qt::node<qt::point> check(100, 100, 100, 100);

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
				}
			}

			/*if (event.type == sf::Event::MouseMoved){
				check.x = sf::Mouse::getPosition(*window).x;
				check.y = sf::Mouse::getPosition(*window).y;
			}*/
		}

		window->clear(sf::Color::Black);

		// qt->show(window, sf::Color::Transparent);
		// showNode(window, check, sf::Color::Cyan);

		for(auto&& point : qt::point::points) {
			point->move();
		}

		qt->update();
				
		qt->collide();

		for(auto&& point : qt::point::points) {
			window->draw(point->c);
		}

	
		window->display();

		time = clock.getElapsedTime();
	    clock.restart().asSeconds();
		std::cout << 1.0f/time.asSeconds() << std::endl;
	}
}

void app::showNode(sf::RenderWindow *window, qt::node<qt::point> node, sf::Color color){
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