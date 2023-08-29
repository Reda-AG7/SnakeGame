#include "Snake.h"

Snake::Snake(const float& boardWidth, const float& boardHeight, const sf::RectangleShape& gameBoard)
{
	isEaten = false;
	radius = 10.0f;
	isCollided = false;
	this->gameBoard = gameBoard;
	for (int i = 0; i < 3; i++) {
		sf::RectangleShape* rect = new sf::RectangleShape(sf::Vector2f(radius, radius));
		rect->setFillColor(sf::Color::White);
		rect->setPosition(5.0f + radius*i,200.0f);
		rect->setOutlineThickness(1u);
		rect->setOutlineColor(sf::Color::Yellow);
		snake.push_back(rect);
	}
	snake.back()->setFillColor(sf::Color::Green);
}

Snake::~Snake()
{
	for (auto i : snake)
		delete i;
}

void Snake::update(float& dt, sf::Keyboard::Key& k, const sf::Vector2f& foodLocation) {
	std::list<sf::RectangleShape*>::iterator it = snake.begin();
	auto it2 = it;
	it2++;
	while (it != snake.end()) {

		//Update last element (Head)
		if (*it == snake.back()) {
			if (k == sf::Keyboard::D)
				(*it)->move(sf::Vector2f(radius, 0.0f));
			else if (k == sf::Keyboard::A)
				(*it)->move(sf::Vector2f(-radius, 0.0f));
			else if (k == sf::Keyboard::W)
				(*it)->move(sf::Vector2f(0.0f, -radius));
			else if (k == sf::Keyboard::S)
				(*it)->move(sf::Vector2f(0.0f, radius));
			return;
		}
		if ((*it)->getPosition().y == (*it2)->getPosition().y) {
			if ((*it)->getPosition().x <= (*it2)->getPosition().x) 
				(*it)->move(sf::Vector2f(radius, 0.0f));
			else (*it)->move(sf::Vector2f(-radius, 0.0f));
		}
		
		else if ((*it)->getPosition().x == (*it2)->getPosition().x) {
			if ((*it)->getPosition().y <= (*it2)->getPosition().y)
				(*it)->move(sf::Vector2f(0.0f, radius));
			else (*it)->move(sf::Vector2f(0.0f, -radius));
		}
		collision();
		foodIsEaten(foodLocation);
		it2++;
		it++;
		std::cout << snake.back()->getPosition().x << "," << snake.back()->getPosition().y << std::endl;
	}
	
}


void Snake::render(sf::RenderTarget& target)
{
	for (const auto i : snake)
		target.draw(*i);
}

void Snake::collision()
{
	isCollided = (snake.back()->getPosition().x <= gameBoard.getGlobalBounds().left ||
		snake.back()->getPosition().x >= gameBoard.getGlobalBounds().width ||
		snake.back()->getPosition().y <= gameBoard.getGlobalBounds().top ||
		snake.back()->getPosition().y >= gameBoard.getGlobalBounds().height) ? 1 : 0;
}

bool Snake::getIsCollided() const {
	return isCollided;
}

void Snake::foodIsEaten(const sf::Vector2f& foodLocation)
{
	if (foodLocation == snake.back()->getPosition()) {
		std::cout << "Food location : " << foodLocation.x << "," << foodLocation.y << std::endl;
		std::cout << "back location : " << snake.back()->getPosition().x << "," << snake.back()->getPosition().y << std::endl;
	}
	
	isEaten = (snake.back()->getPosition() == foodLocation) ? true : false;
}

bool Snake::getIsEaten() const
{
	return isEaten;
}

void Snake::growingSnake(sf::Keyboard::Key& k)
{
	snake.back()->setFillColor(sf::Color::White);
	sf::RectangleShape* rect = new sf::RectangleShape(sf::Vector2f(radius,radius));
	rect->setFillColor(sf::Color::Green);
	rect->setOutlineThickness(1u);
	rect->setOutlineColor(sf::Color::Yellow);
	if(k == sf::Keyboard::A) 
		rect->setPosition(sf::Vector2f(snake.back()->getPosition().x - radius, snake.back()->getPosition().y));
	else if (k == sf::Keyboard::D)
		rect->setPosition(sf::Vector2f(snake.back()->getPosition().x + radius, snake.back()->getPosition().y));
	else if (k == sf::Keyboard::W)
		rect->setPosition(sf::Vector2f(snake.back()->getPosition().x , snake.back()->getPosition().y - radius));
	else if (k == sf::Keyboard::S)
		rect->setPosition(sf::Vector2f(snake.back()->getPosition().x, snake.back()->getPosition().y + radius));
	snake.push_back(rect);
}
