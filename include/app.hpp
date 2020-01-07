#ifndef APP_HPP
#define APP_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Window.hpp>


#include "quadtree.hpp"
#include "node.hpp"
#include "point.hpp"

class app {
public:
	app(unsigned int w = 800, unsigned int h = 800);
	~app();

	void base();
	void show();
	void showNode(sf::RenderWindow *window, qt::node node, sf::Color color);

private:
	qt::node size;
	sf::RenderWindow *window;
	qt::QuadTree<qt::point> *qt;
};

#endif // APP_HPP
