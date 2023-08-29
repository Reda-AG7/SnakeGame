#include "Food.h"
#include<iostream>
Food::Food(float boardWidth, float boardHeight)
{
	this->boardHeight = boardHeight;
	this->boardWidth = boardWidth;
	food = new sf::RectangleShape(sf::Vector2f(10.0f, 10.0f));
	float xLocation = 5;
	float yLocation = 100;
	foodLocation.x = xLocation;
	foodLocation.y = yLocation;
	//std::cout << xLocation << "," << yLocation << std::endl;
	food->setPosition(xLocation, yLocation);
	food->setFillColor(sf::Color::Magenta);
}

Food::~Food()
{
	delete food;
}

void Food::update(float& dt)
{
}

void Food::render(sf::RenderTarget& target)
{
	target.draw(*food);
}

sf::Vector2f Food::getFoodLocation() const
{
	return foodLocation;
}

void Food::updatePosition()
{
	float xLocation = 5 + (rand() % (int)(boardWidth/10 - 5))*10;
	float yLocation = 110 + (rand() % (int)((boardHeight-110)/10))*10;
	//std::cout << "New foodLocation : " << xLocation << "," << yLocation << std::endl;
	food->setPosition(xLocation, yLocation);
	foodLocation = food->getPosition();
}
