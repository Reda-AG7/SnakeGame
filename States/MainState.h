#pragma once
#include "State.h"
#include "GameState.h"
#include "../Components/Button.h";

class MainState :
    public State
{
private:
    float width, height;
    //Title
    Text* GameTitle;
    Text* scoreText;
    //Buttons
    Button* playButton;
    Button* quitButton;
    
    std::string bestScore;
public:
    MainState(sf::RenderWindow&, std::stack<State*>&);
    ~MainState();
    void update(float&);
    void render(sf::RenderTarget&);
    void initButtons();
    void initRecord();
};

