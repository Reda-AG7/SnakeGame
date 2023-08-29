#pragma once
#include "State.h"
#include "../Components/Button.h"
#include<chrono>
#include "PauseState.h"
#include "../Components/Snake.h"
#include "../Components/Food.h"

class GameState : public State{
	private:
		float width, height;
		Text* time;
		unsigned score;
		Text* scoreText;
		Button* pause;
		unsigned seconds, minutes;
		std::chrono::steady_clock::time_point startTime, currentTime;

		sf::RectangleShape* gameBoard;
		Snake* player;
		sf::Keyboard::Key k;

		Food* food;
		bool validKeyPressed;

	public:
		GameState(sf::RenderWindow&, std::stack<State*>&);
		~GameState();
		void update(float&);
		void render(sf::RenderTarget&);
		void updateTime();
		void initGameBoard();
		void updateKeyboard();
};

