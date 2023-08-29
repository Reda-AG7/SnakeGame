#pragma once
#include "../include/SFML/Graphics.hpp"
#include<iostream>
#include<list>

class Snake
{
	private:
		std::list<sf::RectangleShape*> snake;
		float radius;
		sf::Vector2f oldMove;
		sf::RectangleShape gameBoard;
		bool isCollided;
		bool isEaten;
	public:
		Snake(const float&, const float&,const sf::RectangleShape&);
		~Snake();
		void update(float&, sf::Keyboard::Key&, const sf::Vector2f&);
		void render(sf::RenderTarget&);
		void collision();
		bool getIsCollided() const;
		void foodIsEaten( const sf::Vector2f&);
		bool getIsEaten() const;
		void growingSnake(sf::Keyboard::Key&);
};
