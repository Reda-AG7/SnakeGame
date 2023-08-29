#pragma once
#include "Text.h"

class Button
{
private:
	std::string btnText;
	Text* text;
	sf::RectangleShape rect;
	sf::Color btnIdleColor, btnHoverColor, btnActiveColor;

	float pos_x, pos_y, width, height;
	bool isPressed;
public:
	Button(float, float, float, float, const std::string&, sf::Font&);
	~Button();
	void update(float&, sf::Vector2f);
	void render(sf::RenderTarget&);
	bool buttonPressed() const;
	void initRect();
};

