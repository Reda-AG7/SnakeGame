#pragma once
#include "../include/SFML/Graphics.hpp"
#include "Text.h"

class TextBox
{
private:
	sf::RectangleShape* rect;
	Text* text;
	std::string input;
public:
	TextBox(float, float, float, float, unsigned, sf::Font&);
	~TextBox();
	void update(float&, const std::string&);
	void render(sf::RenderTarget&);
	void initBackground(float&, float&, float&, float&);
};

