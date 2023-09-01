#include "Game.h"

Game::Game()
{
	initWindow();
	initState();
	playerName = "";
}

Game::~Game()
{
	while (!states.empty()) {
		delete states.top();
		states.pop();
	}
	delete window;
}

void Game::updateEvents()
{
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed) {
			window->close();
			exit(EXIT_SUCCESS);
		}
		if (event.type == sf::Event::TextEntered && states.size() == 3) {
			if (event.text.unicode ==8 && playerName.length() > 0) playerName.pop_back();
			else if (((event.text.unicode >= 65 && event.text.unicode <= 90) ||
				(event.text.unicode >= 97 && event.text.unicode <= 122)) && playerName.length() < 8) {
				 playerName += toupper((char)event.text.unicode);
				 states.top()->setPlayerName(playerName);
			}
		}
	}	
}

void Game::update(float dt)
{
	updateEvents();
	if (!states.empty())
		states.top()->update(dt);
	else exit(EXIT_SUCCESS);
	//Update player's Name
	if (states.size() < 3) playerName = "";
}

void Game::render()
{
	window->clear();

	if (!states.empty())
		states.top()->render(*window);

	window->display();
}

void Game::run()
{
	while (window->isOpen()) {
		update(dt);
		render();
	}
}

void Game::initState()
{
	states.push(new MainState(*window, states));
}

void Game::initWindow()
{
	std::fstream fileObj("Config/window.ini");
	if (fileObj.is_open()) {
		//Fetch data from window config file
		getline(fileObj,GameTitle);
		fileObj >> vm.width;
		fileObj >> vm.height;
		fileObj >> maxFrames;
		fileObj >> verticalSyncEnable;
		//Window Initialization
		window = new sf::RenderWindow(vm, GameTitle);
		window->setFramerateLimit(maxFrames);
		window->setVerticalSyncEnabled(verticalSyncEnable);
		fileObj.close();
	}
	else throw("file doesn't exist");
}
