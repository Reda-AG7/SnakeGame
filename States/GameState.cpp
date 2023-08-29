#include "GameState.h"

GameState::GameState(sf::RenderWindow& window, std::stack<State*>& states) : State(window, states)
{
	width = window.getSize().x;
	height = window.getSize().y;
	score = 0u;
	
	time = new Text(width / 2.0f, 40.0f, "00:00", regularTextFont, 28u, sf::Color::White);
	scoreText = new Text(width - 80.0f, 40.0f, "Score: "+std::to_string(score), regularTextFont, 28u, sf::Color(255, 191, 0));
	pause = new Button(80.0f, 20.0f, 100.0f, 50.0f, "Pause", regularTextFont);
	background->setFillColor(sf::Color::Black);

	//Time
	seconds = 0u;
	minutes = 0u;
	startTime = currentTime = std::chrono::steady_clock::now();

	//GameBoard
	initGameBoard();

	player = new Snake(gameBoard->getGlobalBounds().width, gameBoard->getGlobalBounds().height, *gameBoard);
	k = sf::Keyboard::D;

	validKeyPressed = false;
	food = new Food(gameBoard->getLocalBounds().width, gameBoard->getLocalBounds().height);
}

GameState::~GameState()
{
	delete time;
	delete pause;
	delete scoreText;
	delete gameBoard;
	delete player;
	delete food;
}

void GameState::update(float& dt)
{
	//Time
	updateTime();
	time->update(dt);
	
	pause->update(dt, sf::Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y));
	if (pause->buttonPressed()) {
		// present another state ... 
		states->push(new PauseState(*window, *states));
	}
	updateKeyboard();
	player->update(dt, k, food->getFoodLocation());
	//std::cout << food->getFoodLocation().x << "," << food->getFoodLocation().y << std::endl;
	//if (player->getIsCollided()) {
		//GameOver
		//throw("Game Over");
	//}
	if (player->getIsEaten()) {
		//increase the size of the snake
		player->growingSnake(k);
		//update the position of the food
		food->updatePosition();
	}
	
}

void GameState::render(sf::RenderTarget& target)
{
	target.draw(*background);
	scoreText->render(target);
	time->render(target);
	pause->render(target);
	target.draw(*gameBoard);
	food->render(target);
	player->render(target);
	
}

void GameState::updateTime()
{
	currentTime = std::chrono::steady_clock::now();
	seconds = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
	if (seconds == 60u) {
		startTime = std::chrono::steady_clock::now();
		minutes++;
	}
	std::string minutesString = minutes / 10u > 0 ? std::to_string(minutes) + " : " : "0" + std::to_string(minutes) + " : ";
	std::string secondsString = seconds / 10u > 0 ? std::to_string(seconds) : "0" + std::to_string(seconds);
	std::string temp = minutesString + secondsString;
	time->setContent(temp);
}

void GameState::initGameBoard()
{
	gameBoard = new sf::RectangleShape(sf::Vector2f(width-10.0f, height-105.0f));
	gameBoard->setPosition(5.0f, 100.f);
	gameBoard->setOutlineThickness(5.0f);
	gameBoard->setOutlineColor(sf::Color(255, 191, 0));
	gameBoard->setFillColor(sf::Color::Black);
}

void GameState::updateKeyboard() {
	auto temp = k;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		k = temp != sf::Keyboard::D ? sf::Keyboard::A : temp;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		k = temp != sf::Keyboard::W ? sf::Keyboard::S : temp;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		k = temp != sf::Keyboard::A ? sf::Keyboard::D : temp;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		k = temp != sf::Keyboard::S ? sf::Keyboard::W : temp;
	}
}