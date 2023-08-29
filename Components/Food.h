#pragma once
#include "../include/SFML/Graphics.hpp"
#include <random>
class Food
{
private:
	sf::RectangleShape* food;
	sf::Vector2f foodLocation;
	float boardWidth, boardHeight;
public:
	Food(float, float);
	~Food();
	void update(float&);
	void render(sf::RenderTarget&);
	sf::Vector2f getFoodLocation() const;
	void updatePosition();
	
};

