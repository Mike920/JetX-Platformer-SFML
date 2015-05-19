#pragma once
#include "GameState.h"
#include "Game.h"

class PauseState : public GameState
{
private:
	sf::RenderWindow& mWindow;
	sf::Font mFont;
	std::vector<sf::Text> mOptions;
	int mOptionIndex;
public:
	PauseState(sf::RenderWindow& window);
	~PauseState(void);

	virtual void update(sf::Time dt);
	virtual void draw();
	virtual void handleEvent(sf::Event e);

	void updateText();
};

