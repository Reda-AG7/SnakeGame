#pragma once
#include "State.h"
#include<chrono>
#include "../Components/Button.h"

class PauseState :
    public State
{
private:
    Button* resume;
    Button* newGame;
    Button* quit;

public:
    PauseState(sf::RenderWindow&, std::stack<State*>&);
    ~PauseState();
    void update(float&);
    void render(sf::RenderTarget&);
};

