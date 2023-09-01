#include "GameOverState.h"

GameOverState::GameOverState(sf::RenderWindow& window, std::stack<State*>& states, unsigned& rec) : State(window, states)
{
	record = rec;
	this->window = &window;
	background->setFillColor(sf::Color::Black);

	title = new Text(window.getSize().x / 2.0f, 200.0f, "GAME OVER", titleFont, 40u, sf::Color::Red);

	textBox = new TextBox(window.getSize().x / 2.0f, 400.0f, 150.0f, 50.0f, 20u, regularTextFont);
	save = new Button(window.getSize().x / 2.0f, 500.0f, 150.0f, 50.0f,"Save", regularTextFont);

	playerName = "";
}

GameOverState::~GameOverState()
{
	delete save;
	delete title;
	delete textBox;
}

void GameOverState::update(float& dt)
{
	sf::Vector2f mousePosition = sf::Vector2f(static_cast<float>(sf::Mouse::getPosition(*window).x),
		static_cast<float>(sf::Mouse::getPosition(*window).y));
	sf::Event e;
	//collectText(e);
	textBox->update(dt, playerName);

	save->update(dt, mousePosition);
	if (save->buttonPressed()) {
		//update the record
		updateRecord(record);
		while (states->size() > 1)
			states->pop();
		
	}
}

void GameOverState::render(sf::RenderTarget& target)
{
	target.draw(*background);
	title->render(target);
	save->render(target);
	textBox->render(target);
}

void GameOverState::setPlayerName(const std::string& textInput)
{
	playerName = textInput;
}

void GameOverState::updateRecord(unsigned& record) const
{
	std::fstream fObj;
	fObj.open("Config/bestRecord.ini", std::ios::in);
	unsigned oldRec = 0;
	std::string oldRecordHolder = "";
	std::vector<std::pair<std::string, unsigned>> temp;
	if (fObj.is_open()) {
		while (!fObj.eof()) {
			fObj >> oldRecordHolder;
			fObj >> oldRec;
			temp.push_back(std::make_pair(oldRecordHolder, oldRec));
		}
		
		temp.push_back(std::make_pair(playerName,record));
		typedef std::pair<std::string, unsigned> myP;
		struct comp {
			bool operator()(myP a,myP b) {
				return a.second > b.second;
			}
		};
		comp compare;
		std::sort(temp.begin(), temp.end(), compare);
		temp.resize(3);
		fObj.close();
		fObj.open("Config/bestRecord.ini", std::ios::out);
		if (fObj.is_open()) {
			for (const auto& p : temp) {
				fObj << p.first;
				fObj << " ";
				fObj << p.second;
				fObj << "\n";
			}
			fObj.close();
		}
		else {
			std::cout << "File is not opened\n";
		}
	}
	else {
		std::cerr << "file is not found\n";
	}
}
