#pragma once
#include "SFML/Graphics.hpp"
#include<iostream>
#include<stack>
#include <fstream>
class Text
{
private:
	sf::Text text;
	std::string content;
	float pos_x, pos_y;
	float width, height;
	unsigned characterSize;
	sf::Color textColor;
public:
	Text(float, float, const std::string&, sf::Font&, unsigned, const sf::Color&);
	~Text();
	void update(float&);
	void render(sf::RenderTarget&);
	void setContent(std::string&);
};

