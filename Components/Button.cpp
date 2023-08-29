#include "Button.h"

Button::Button(float pos_x, float pos_y, float width, float height, const std::string& title, sf::Font& font)
{
	this->pos_x = pos_x;
	this->pos_y = pos_y;
	this->width = width;
	this->height = height;

	btnIdleColor = sf::Color(25, 25, 25);
	btnHoverColor = sf::Color(128, 128, 128);
	btnActiveColor = sf::Color(140, 140, 140);

	initRect();
	
	//initTexture();
	isPressed = false;

	
	text = new Text(pos_x, pos_y + height/2.0f, title, font, 28u, sf::Color(178,190,181));

}

Button::~Button() {
	delete text;
}

void Button::update(float& dt,sf::Vector2f mousePosition) {
	
	if (rect.getGlobalBounds().contains(mousePosition)) {
		//Hover
		isPressed = false;
		rect.setFillColor(btnHoverColor);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			//pressed
			isPressed = true;
			rect.setFillColor(btnActiveColor);
		}
	}
	else {
		isPressed = false;
		rect.setFillColor(btnIdleColor);
	}
	
}

void Button::render(sf::RenderTarget& target) {
	target.draw(rect);
	text->render(target);
}

bool Button::buttonPressed() const
{
	return isPressed;
}

void Button::initRect()
{
	rect.setSize(sf::Vector2f(width, height));
	rect.setPosition(sf::Vector2f(pos_x - width / 2.0f, pos_y));
	rect.setFillColor(btnIdleColor);
	rect.setOutlineThickness(1u);
	rect.setOutlineColor(sf::Color(178, 190, 181));
}


