#include "Game.h"

Game::Game()
{
	initWindow();
	initState();
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
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed) {
			window->close();
			exit(EXIT_SUCCESS);
		}
	}
}

void Game::update(float dt)
{
	updateEvents();
	if (!states.empty())
		states.top()->update(dt);
	else exit(EXIT_SUCCESS);
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
