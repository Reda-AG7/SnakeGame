#include "TextBox.h"


TextBox::TextBox(float pos_x, float pos_y, float width, float height, unsigned characterSize, sf::Font& font)
{
	initBackground(pos_x, pos_y, width, height);
	input = "your name";
	text = new Text(pos_x, pos_y + height/2.0f,input, font, characterSize, sf::Color(28, 28, 28));
}

TextBox::~TextBox()
{
	delete text;
	delete rect;
}

void TextBox::update(float& dt, const std::string& inputText)
{
	if (inputText.length() > 0) {
		input = inputText;
	}
	else input = "your name";
	text->setContent(input);
	text->update(dt);
}

void TextBox::render(sf::RenderTarget& target)
{
	target.draw(*rect);
	text->render(target);
}

void TextBox::initBackground(float& pos_x, float& pos_y, float& width, float& height)
{
	rect = new sf::RectangleShape(sf::Vector2f(width, height));
	rect->setPosition(pos_x - width/2.0f, pos_y);
	rect->setOutlineThickness(2u);
	rect->setOutlineColor(sf::Color(178, 190, 181));
}
