#ifndef __GAME__H
#define __GAME__H


#include "States/MainState.h"
#include<stack>
#include<fstream>
#include<string>

class Game
{
private:
	sf::RenderWindow* window;
	sf::VideoMode vm;
	std::string GameTitle;
	std::stack<State*> states;
	float dt;
	bool verticalSyncEnable;
	unsigned maxFrames;
	
public:
	Game();
	~Game();
	void updateEvents();
	void update(float);
	void render();
	void run();
	void initState();
	void initWindow();

};

#endif

