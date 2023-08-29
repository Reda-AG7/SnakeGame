#include "MainState.h"

MainState::MainState(sf::RenderWindow& window, std::stack<State*>& states)
	: State(window, states)
{
	bestScore = "Record\nUnkown: 000";
	width = window.getSize().x;
	height = window.getSize().y;

	backgroundColor = sf::Color(25,25,25);
	background->setFillColor(backgroundColor);

	//Init Game title
	GameTitle = new Text(width / 2.0f, 100.0f, "Snake Game", titleFont, 40u, sf::Color::White);
	
	//Init Buttons
	initButtons();
	initRecord();
	scoreText = new Text(100.0f, 50.0f, bestScore, regularTextFont, 25u, sf::Color::White);
}

MainState::~MainState()
{
	delete GameTitle;
	delete scoreText;
	delete playButton;
	delete quitButton;
}

void MainState::update(float& dt)
{
	playButton->update(dt, sf::Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y));
	if (playButton->buttonPressed()) {
		states->push(new GameState(*window, *states));
	}
	//Quit Button
	quitButton->update(dt, sf::Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y));
	if (quitButton->buttonPressed()) {
		states->pop();
	}
}

void MainState::render(sf::RenderTarget& target)
{
	target.draw(*background);
	GameTitle->render(target);
	scoreText->render(target);

	playButton->render(target);
	quitButton->render(target);
}

void MainState::initButtons()
{
	playButton = new Button(width / 2.0f, 500.0f, 170.0f, 50.0f, "Play", regularTextFont);
	quitButton = new Button(width / 2.0f, 570.0f, 170.0f, 50.0f, "Quit", regularTextFont);
}

void MainState::initRecord()
{
	std::fstream* fObj = new std::fstream();
	fObj->open("record.ini");
	if (fObj->is_open()) {
		std::getline(*fObj, bestScore);
		fObj->close();
		delete fObj;
	}
	else {
		std::cout << "File couldn't be opened\n";
		//exit(EXIT_FAILURE);
	}
}


