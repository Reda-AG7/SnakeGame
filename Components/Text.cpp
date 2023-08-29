#include "Text.h"

Text::Text(float pos_x, float pos_y, const std::string& content, sf::Font& font, unsigned characterSize, const sf::Color& color)
{
	this->pos_x = pos_x;
	this->pos_y = pos_y;
	this->characterSize = characterSize;
	this->content = content;
	text.setString(content);
	text.setFont(font);
	text.setFillColor(color);
	text.setCharacterSize(characterSize);
	sf::FloatRect textRec = text.getLocalBounds();
	text.setOrigin(textRec.left + textRec.width / 2.0f, textRec.top + textRec.height/2.0f);
	text.setPosition(sf::Vector2f(pos_x,pos_y));
}

Text::~Text()
{
}

void Text::update(float& dt)
{
	
	text.setString(content);
	//std::cout << content << std::endl;
}

void Text::render(sf::RenderTarget& target)
{
	target.draw(text);
}

void Text::setContent(std::string& c)
{
	content = c;
}


