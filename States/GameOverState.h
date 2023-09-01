#pragma once
#include "State.h"
#include "../Components/Button.h"
#include "../Components/TextBox.h"
#include<fstream>

class GameOverState : public State
{
private:
	Text* title;
	TextBox* textBox;
	Button* save;
	sf::RenderWindow* window;
	std::string playerName;
	unsigned record;
public:
	GameOverState(sf::RenderWindow&, std::stack<State*>&, unsigned&);
	~GameOverState();
	void update(float&);
	void render(sf::RenderTarget&);
	void setPlayerName(const std::string&);
	void updateRecord(unsigned&) const;
};

