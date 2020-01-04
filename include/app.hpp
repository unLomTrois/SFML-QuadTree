#ifndef APP_HPP
#define APP_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Window.hpp>

#include "point.hpp"
#include "node.hpp"
#include "quadtree.hpp"


class app {
public:
	app(unsigned int w = 800, unsigned int h = 800);
	~app();

	void base();
	void show();
	void showNodes(sf::RenderWindow *window, qt::QuadTree *qt, sf::Color color = sf::Color::Green);

private:
	qt::node size;
	sf::RenderWindow *window;
	// std::vector<qt::point*> points;
	qt::QuadTree qt;
};

#endif // APP_HPP
