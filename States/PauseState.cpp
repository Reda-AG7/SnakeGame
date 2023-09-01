#include "PauseState.h"

PauseState::PauseState(sf::RenderWindow& window, std::stack<State*>& states) : State(window, states)
{
	background->setSize(sf::Vector2f(300.0f, static_cast<float>(window.getSize().y)));
	background->setPosition(window.getSize().x / 2.0f, 0.0f);
	background->setFillColor(sf::Color::Transparent);

	//Buttons
	resume = new Button(window.getSize().x / 2.0f, 300.0f, 200.0f, 50.0f, "Resume", regularTextFont);
	quit = new Button(window.getSize().x / 2.0f, 440.0f, 200.0f, 50.0f, "Quit", regularTextFont);
	newGame = new Button(window.getSize().x / 2.0f, 370.0f, 200.0f, 50.0f, "New Game", regularTextFont);
}

PauseState::~PauseState()
{
	delete resume;
	delete quit;
	delete newGame;
}

void PauseState::update(float& dt)
{
	sf::Vector2f mousPosition = sf::Vector2f(static_cast<float>(sf::Mouse::getPosition(*window).x),
		static_cast<float>(sf::Mouse::getPosition(*window).y));
	resume->update(dt, mousPosition);
	if (resume->buttonPressed())
		states->pop();
	
		
	quit->update(dt, mousPosition);
	if (quit->buttonPressed()) {
		while (!states->empty()) {
			states->pop();
		}
	}
	newGame->update(dt, mousPosition);
	if (newGame->buttonPressed()) {
		while (states->size() > 1) 
			states->pop();
	}
}

void PauseState::render(sf::RenderTarget& target)
{
	target.draw(*background);
	resume->render(target);
	quit->render(target);
	newGame->render(target);
}
