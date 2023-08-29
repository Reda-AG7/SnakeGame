#ifndef __STATE__H
#define __STATE__H

#include "SFML/Graphics.hpp"
#include<iostream>
#include<stack>

class State
{
protected:
	sf::RectangleShape* background;
	sf::Color backgroundColor;
	sf::Font titleFont;
	sf::Font regularTextFont;

	sf::RenderWindow* window;

	std::stack<State*>* states;

public:
	State();
	State(sf::RenderWindow&, std::stack<State*>&);
	virtual ~State();
	virtual void update(float&) = 0;
	virtual void render(sf::RenderTarget&) = 0;
};


#endif

