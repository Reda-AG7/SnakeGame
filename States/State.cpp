#include "State.h"

State::State(sf::RenderWindow& window, std::stack<State*>& states) {
	this->window = &window;
	this->states = &states;
	background = new sf::RectangleShape(sf::Vector2f(window.getSize().x, window.getSize().y));

	//Fonts
	titleFont.loadFromFile("Fonts/Shrikhand-Regular.ttf");
	regularTextFont.loadFromFile("Fonts/Dosis-Regular.ttf");
}

State::~State() {
	delete background;
}

void State::setPlayerName(const std::string&)
{
}
